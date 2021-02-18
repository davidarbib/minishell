/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:17:38 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/18 21:37:22 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del(void *arg)
{
	free(arg);
}

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
		ft_lstdel_first(&g_all_childs, del);
	}
}

/*
** pipe_stdin = 0 for the first process of stdin
*/

void	eval(t_pipeline *pipeline, int pipe_stdin)
{
	int			p[2];
	int			next_stdin;

	next_stdin = 0;
	if (!pipeline)
		return ;
	if (pipeline->next)
	{
		pipe(p);
		next_stdin = p[0];
	}
	launch(pipeline->content, pipeline->next ? 1 : 0, pipe_stdin, p);
	eval(pipeline->next, next_stdin);
}

void	eval_list(t_shell_list *list)
{
	int run_in_subprocess;
	int	old_in;
	int	old_out;

	run_in_subprocess = 1;
	if (!list)
		return ;
	set_redirections((t_pipeline*)list->content);
	g_temp_redirections = g_redirections;
	if ((t_pipeline*)list->content && !((t_pipeline*)list->content)->next &&
			is_built_in(((t_pipeline*)list->content)->content))
	{
		old_in = dup(0);
		old_out = dup(1);
		use_redirections();
		g_last_command_result =
			launch_built_in(((t_pipeline*)list->content)->content);
		dup2(old_in, 0);
		close(old_in);
		dup2(old_out, 1);
		close(old_out);
	}
	else
	{
		eval(list->content, 0);
		wait_all_childs();
	}
	ft_lstclear(&g_redirections, close_and_free);
	eval_list(list->next);
}
