/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:17:38 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/17 10:58:51 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	run_in_subprocess = 1;
	if (!list)
		return ;
	if ((t_pipeline*)list->content && !((t_pipeline*)list->content)->next &&
			is_built_in(((t_pipeline*)list->content)->content))
	{
		//use_redirections(simple_command);
		g_last_command_result =
			launch_built_in(((t_pipeline*)list->content)->content);
	}
	else
		eval(list->content, 0);
	eval_list(list->next);
}
