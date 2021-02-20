/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:55:43 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/20 13:53:21 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	use_pipes(t_pipe pipe)
{
	if (pipe.pipe_stdin != 0)
	{
		dup2(pipe.pipe_stdin, 0);
		close(pipe.pipe_stdin);
	}
	if (pipe.is_next_in_pipeline)
	{
		dup2(pipe.p[1], 1);
		close(pipe.p[1]);
		close(pipe.p[0]);
	}
}

void	use_redirections(void)
{
	int in;
	int out;

	in = ((t_redirection*)g_temp_redirections->content)->in;
	out = ((t_redirection*)g_temp_redirections->content)->out;
	if (in != 0)
		dup2(in, 0);
	if (out != 1)
		dup2(out, 1);
	g_temp_redirections = g_temp_redirections->next;
}

void	treat_redir(t_io_redirect *redir, t_redirection *redirection)
{
	if (redir->type == i_redirect)
	{
		if (redirection->in != 0)
			close(redirection->in);
		if ((redirection->in = open(redir->filename, O_RDONLY)) < 0)
			exit(EXIT_FAILURE);
	}
	else
	{
		if (redirection->out != 1)
			close(redirection->out);
		if ((redirection->out =
				open(redir->filename, O_WRONLY | O_CREAT |
				(redir->type == oc_redirect ? 0 : O_APPEND), 0644)) < 0)
			exit(EXIT_FAILURE);
	}
}

void	set_redirections(t_pipeline *pipeline)
{
	t_list			*redir_list;
	t_redirection	*redirection;

	if (!pipeline)
		return ;
	redir_list = ((t_simple_command*)pipeline->content)->redirections;
	redirection = malloc(sizeof(t_redirection));
	redirection->in = 0;
	redirection->out = 1;
	while (redir_list)
	{
		treat_redir(redir_list->content, redirection);
		redir_list = redir_list->next;
	}
	ft_lstadd_back_elem(&g_redirections, redirection);
	set_redirections(pipeline->next);
}

void	close_unused_in_parent(t_pipe pipe)
{
	if (pipe.is_next_in_pipeline)
		close(pipe.p[1]);
	if (pipe.pipe_stdin != 0)
		close(pipe.pipe_stdin);
}
