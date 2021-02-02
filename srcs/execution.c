/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:27:57 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/01 21:45:30 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *arg)
{
	free(arg);
}

int		cmp(void *process, void *pid_ref)
{
	return (((t_process*)process)->pid - *(int*)pid_ref);
}

void	wait_all_childs(void)
{
	int			status;
	int			stopped_pid;

	while (1)
	{
		stopped_pid = waitpid(-1, &status, WUNTRACED);
		ft_lstremove_if(&g_all_childs, &stopped_pid, cmp, del);
		if (!g_all_childs)
			break ;
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
}

void	redirect_and_launch(t_pipeline *pipeline, int pipe_stdin,
									int p[])
{
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
	launch(((t_simple_command*)pipeline->content)->args);
}
