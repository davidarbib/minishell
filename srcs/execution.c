/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:13:29 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/05 14:14:23 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	del(void *arg)
{
	free(arg);
}

void	ft_lstdel_first(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	
	tmp = (*lst)->next;
	del((*lst)->content);
	free(*lst);
	*lst = tmp;
}

void	wait_all_childs(void)
{
	int			status;
	int			pid;

	while (1)
	{
		if (!g_all_childs)
			break ;
		pid = ((t_process*)g_all_childs->content)->pid;
		waitpid(pid, &status, WUNTRACED);
		ft_lstdel_first(&g_all_childs, del);
	}
}

void	launch(t_list *command)
{
	char	**tab;
	int		size;

	tab = (char**)ft_lsttotab(command, 8, &size);
	/*ft_lstclear(command, del);*/
	tab[size] = 0;
	execve((char*)tab[0], (char*const*)tab, NULL);
	perror("minishell");
	exit(EXIT_FAILURE);
}

void	redirect_and_launch(t_pipeline *pipeline, int pipe_stdin,
									int p[])
{
	t_simple_command	command;
	t_list				*redir_list;
	t_io_redirect		redir;
	int					*fd;

	command = *(t_simple_command*)pipeline->content;
	if (pipe_stdin != -1)
	{
		dup2(pipe_stdin, 0);
		close(pipe_stdin);
	}
	if (pipeline->next)
	{
		dup2(p[1], 1);
		close(p[1]);
		close(p[0]);
	}
	redir_list = command.redirections;
	while (redir_list)
	{
/*<<<<<<< HEAD
		current_redir = *(t_io_redirect*)redir_list->content;
		if (current_redir.type == i_redirect)
		{
			if ((fd = open(current_redir.filename, O_RDONLY)) < 0)
			{
				perror("minishell");
				return ;
			}
			// [io_number]<word
			dup2(fd, current_redir.io_number == -1 ?
									0 : current_redir.io_number);
		}
		else {
			// [io_number]>word ou [io_number]>>word
			if ((fd = open(current_redir.filename,
							current_redir.type == oc_redirect ? O_WRONLY : O_WRONLY | O_APPEND)))
		}

=======*/
		redir = *(t_io_redirect*)redir_list->content;
		fd = malloc(sizeof(int));
		if (redir.type == i_redirect)
		{
			printf("redirecting stdin to %s\n", redir.filename);
			*fd = open(redir.filename, O_RDONLY);
			ft_lstadd_front_elem(&g_open_fds, fd);
			dup2(*fd, redir.io_number == -1 ? 0 : redir.io_number);
		}
		else
		{
			printf("redirecting stdout to %s\n", redir.filename);
			if (redir.type == oc_redirect)
				*fd = open(redir.filename, O_WRONLY | O_CREAT, 0644);
			else
				*fd = open(redir.filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			ft_lstadd_front_elem(&g_open_fds, fd);
			dup2(*fd, redir.io_number == -1 ? 1 : redir.io_number);
		}
		fprintf(stderr, "redirs end\n");
>>>>>>> 0a9f93349d3cc8bdbec5006948ddb6b341771fca
		redir_list = redir_list->next;
	}
	launch(command.args);
}
