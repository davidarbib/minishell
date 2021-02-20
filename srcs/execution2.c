/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 10:36:52 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/20 10:44:02 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pid(int pid, t_temp temp)
{
	int		*pid_ptr;

	if (!(pid_ptr = malloc(sizeof(int))))
	{
		free_before_exit(NULL, temp.file, temp.tab, temp.env);
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	*pid_ptr = pid;
	ft_lstadd_front_elem(&g_all_childs, pid_ptr);
}

void	run_in_subprocess(t_simple_command *simple_command,
								t_pipe pipe, t_temp temp)
{
	use_pipes(pipe);
	use_redirections();
	if (is_built_in(simple_command))
		exit(launch_built_in(simple_command));
	else
	{
		execve(temp.file, (char*const*)temp.tab, temp.env);
		perror("minishell");
		exit(EXIT_FAILURE);
	}
}
