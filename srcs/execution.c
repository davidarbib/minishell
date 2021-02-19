/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:13:29 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/19 16:07:18 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>

char	*try_this_path(char *prefix, char *command, size_t command_length)
{
	size_t		l1;
	char		*concatenated;
	struct stat	buf;

	l1 = ft_strlen(prefix);
	concatenated = malloc(l1 + command_length + 2);
	ft_strlcpy(concatenated, prefix, l1 + 1);
	concatenated[l1] = '/';
	concatenated[l1 + 1] = 0;
	ft_strlcat(concatenated, command, l1 + command_length + 2);
	if (stat(concatenated, &buf) == 0 && S_ISREG(buf.st_mode))
		return (concatenated);
	free(concatenated);
	return (NULL);
}

char	*try_this_command(char *command)
{
	struct stat	buf;
	char		*result;

	result = ft_strdup(command);
	if (stat(result, &buf) == 0 && S_ISREG(buf.st_mode))
		return (result);
	free(result);
	return (NULL);
}

char	*find_in_path(char *command)
{
	char		**tab;
	char		**tab_mem;
	char		*path;
	char		*result;
	size_t		l2;

	path = ft_getenv("PATH", g_env);
	if (path)
	{
		tab = ft_split(path, ':');
		tab_mem = tab;
		l2 = ft_strlen(command);
		while (*tab)
		{
			if ((result = try_this_path(*tab, command, l2)))
			{
				free(tab_mem);
				return (result);
			}
			free(result);
			tab++;
		}
		free_tab(tab_mem);
	}
	return (try_this_command(command));
}

void	close_unused_in_parent(t_pipe pipe)
{
	if (pipe.is_next_in_pipeline)
		close(pipe.p[1]);
	if (pipe.pipe_stdin != 0)
		close(pipe.pipe_stdin);
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

void	launch(t_simple_command *simple_command, t_pipe pipe)
{
	int		size;
	t_temp	temp;
	int		pid;

	temp.file = NULL;
	if (!simple_command->args)
		return ;
	temp.tab = (char**)ft_lsttotab(simple_command->args, 8, &size);
	temp.tab[size] = 0;
	temp.env = to_environ_array(g_env);
	if (!is_built_in(simple_command))
		temp.file = find_in_path(temp.tab[0]);
	if (!temp.file)
	{
		free_and_continue(NULL, NULL, temp.tab, temp.env);
		g_last_command_result = 127;
		printf("here\n");
		perror("minishell");
		return ;
	}
	if ((pid = fork()) == 0)
		run_in_subprocess(simple_command, pipe, temp);
	else if (pid < 0)
		perror("minishell");
	close_unused_in_parent(pipe);
	add_pid(pid, temp);
	free_and_continue(NULL, temp.file, temp.tab, temp.env);
}
