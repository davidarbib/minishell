/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 10:36:52 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/20 17:48:18 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pid(int pid)
{
	int		*pid_ptr;

	if (!(pid_ptr = malloc(sizeof(int))))
	{
		free_before_exit(NULL);
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	*pid_ptr = pid;
	ft_lstadd_front_elem(&g_all_childs, pid_ptr);
}

void	run_in_subprocess(t_simple_command *simple_command,
								t_pipe pipe)
{
	int	ret;

	use_pipes(pipe);
	use_redirections();
	if (is_built_in(simple_command))
	{
		ret = launch_built_in(simple_command);
		free_before_exit(NULL);
		exit(ret);
	}
	else
	{
		execve(g_to_be_freed.file,
				(char*const*)g_to_be_freed.tab, g_to_be_freed.env);
		perror("minishell");
		exit(EXIT_FAILURE);
	}
}
