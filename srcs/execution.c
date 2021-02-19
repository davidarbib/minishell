/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:13:29 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/19 15:36:01 by fyusuf-a         ###   ########.fr       */
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

void	close_unused_in_parent(int is_next_in_pipeline, int pipe_stdin,
										int pipe_stdout)
{
	if (is_next_in_pipeline)
		close(pipe_stdout);
	if (pipe_stdin != 0)
		close(pipe_stdin);
}

void	launch(t_simple_command *simple_command, t_pipe pipe)
{
	char	**tab;
	char	**env;
	int		size;
	char	*file;
	int		pid;
	int		*pid_ptr;

	file = NULL;
	if (!simple_command->args)
		return ;
	tab = (char**)ft_lsttotab(simple_command->args, 8, &size);
	tab[size] = 0;
	env = to_environ_array(g_env);
	if (!is_built_in(simple_command))
		file = find_in_path(tab[0]);
	if (!file)
	{
		free_and_continue(NULL, NULL, tab, env);
		g_last_command_result = 127;
		perror("minishell");
		return ;
	}
	if ((pid = fork()) == 0)
	{
		use_pipes(pipe);
		use_redirections();
		if (is_built_in(simple_command))
			exit(launch_built_in(simple_command));
		else
		{
			execve(file, (char*const*)tab, env);
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror("minishell");
	close_unused_in_parent(pipe.is_next_in_pipeline, pipe.pipe_stdin,
							pipe.p[1]);
	if (!(pid_ptr = malloc(sizeof(int))))
	{
		free_before_exit(NULL, file, tab, env);
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	*pid_ptr = pid;
	ft_lstadd_front_elem(&g_all_childs, pid_ptr);
	free_and_continue(NULL, file, tab, env);
}
