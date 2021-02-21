/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:55:43 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/21 10:58:48 by fyusuf-a         ###   ########.fr       */
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

void	use_redirections(int index)
{
	int		in;
	int		out;
	t_list	*tmp;
	int		i;

	tmp = g_redirections;
	i = 0;
	while (i < index)
	{
		tmp = tmp->next;
		i++;
	}
	in = ((t_redirection*)tmp->content)->in;
	out = ((t_redirection*)tmp->content)->out;
	if (in != 0)
		dup2(in, 0);
	if (out != 1)
		dup2(out, 1);
}

int		treat_redir(t_io_redirect *redir, t_redirection *redirection)
{
	if (redir->type == i_redirect)
	{
		if (redirection->in != 0)
			close(redirection->in);
		if ((redirection->in = open(redir->filename, O_RDONLY)) < 0)
		{
			dprintf(2, "minishell: %s: %s\n", redir->filename, strerror(errno));
			return (-1);
		}
	}
	else
	{
		if (redirection->out != 1)
			close(redirection->out);
		redirection->out = open(redir->filename, O_WRONLY | O_CREAT |
				(redir->type == oc_redirect ? O_TRUNC : O_APPEND), 0644);
		if (redirection->out < 0)
		{
			dprintf(2, "minishell: %s: %s\n", redir->filename, strerror(errno));
			return (-1);
		}
	}
	return (0);
}

int		set_redirections(t_pipeline *pipeline)
{
	t_list			*redir_list;
	t_redirection	*redirection;

	if (!pipeline)
		return (0);
	redir_list = ((t_simple_command*)pipeline->content)->redirections;
	redirection = malloc(sizeof(t_redirection));
	redirection->in = 0;
	redirection->out = 1;
	while (redir_list)
	{
		if (treat_redir(redir_list->content, redirection) < 0)
			return (-1);
		redir_list = redir_list->next;
	}
	ft_lstadd_back_elem(&g_redirections, redirection);
	return (set_redirections(pipeline->next));
}

void	close_unused_in_parent(t_pipe pipe)
{
	if (pipe.is_next_in_pipeline)
		close(pipe.p[1]);
	if (pipe.pipe_stdin != 0)
		close(pipe.pipe_stdin);
}
