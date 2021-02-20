/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:17:38 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/20 17:09:08 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand_quote_removal.h"

void		wait_all_childs(void)
{
	int			status;
	int			pid;

	while (1)
	{
		if (!g_all_childs)
			break ;
		pid = *(int*)g_all_childs->content;
		waitpid(pid, &status, WUNTRACED);
		if (!g_all_childs->next)
		{
			if (WIFEXITED(status))
				g_last_command_result = WEXITSTATUS(status);
			if (WIFSTOPPED(status))
				g_last_command_result = 128 + WSTOPSIG(status);
		}
		ft_lstdel_first(&g_all_childs, free);
	}
}

/*
** pipe_stdin = 0 for the first process of stdin
*/

void		eval(t_pipeline *pipeline, int pipe_stdin)
{
	int			next_stdin;
	t_pipe		pip;

	if (!pipeline)
		return ;
	next_stdin = 0;
	if (pipeline->next)
	{
		pipe(pip.p);
		next_stdin = pip.p[0];
	}
	pip.is_next_in_pipeline = pipeline->next != NULL;
	pip.pipe_stdin = pipe_stdin;
	launch(pipeline->content, pip);
	eval(pipeline->next, next_stdin);
}

void		eval_list(t_shell_list *list)
{
	if (!list)
		return ;
	if (set_redirections((t_pipeline*)list->content) == 0)
	{
		g_temp_redirections = g_redirections;
		if (expand_pipeline((t_pipeline*)list->content))
		{
			perror("minishell");
			free_before_exit(NULL);
			exit(EXIT_FAILURE);
		}
		if ((t_pipeline*)list->content && !((t_pipeline*)list->content)->next &&
				is_built_in(((t_pipeline*)list->content)->content))
			prelaunch_built_in(((t_pipeline*)list->content)->content);
		else
		{
			eval(list->content, 0);
			wait_all_childs();
		}
	}
	else
		g_last_command_result = 1;
	ft_lstclear(&g_redirections, close_and_free);
	eval_list(list->next);
}
