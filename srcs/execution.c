/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:27:57 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/03 13:53:50 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *arg)
{
	free(arg);
}

/*int		cmp(void *process, void *pid_ref)
{
	return (((t_process*)process)->pid - *(int*)pid_ref);
}*/

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

		/*stopped_pid = waitpid(-1, &status, WUNTRACED);*/
		/*ft_lstremove_if(&g_all_childs, &stopped_pid, cmp, del);*/
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
	launch(command.args);
}
