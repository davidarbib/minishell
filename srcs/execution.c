/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:13:29 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/20 15:10:28 by fyusuf-a         ###   ########.fr       */
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
				free_tab(tab_mem);
				return (result);
			}
			free(result);
			tab++;
		}
		free_tab(tab_mem);
	}
	return (try_this_command(command));
}

void	init_temp(t_simple_command *simple_command)
{
	int		size;

	g_to_be_freed.file = NULL;
	g_to_be_freed.tab = (char**)ft_lsttotab(simple_command->args, 8, &size);
	g_to_be_freed.tab[size] = 0;
	g_to_be_freed.env = to_environ_array(g_env);
}

void	launch(t_simple_command *simple_command, t_pipe pipe)
{
	int		pid;

	if (!simple_command->args)
		return ;
	init_temp(simple_command);
	if (!is_built_in(simple_command))
		g_to_be_freed.file = find_in_path(g_to_be_freed.tab[0]);
	if (!g_to_be_freed.file)
	{
		free_and_continue(NULL);
		g_last_command_result = 127;
		perror("minishell");
		return ;
	}
	if ((pid = fork()) == 0)
		run_in_subprocess(simple_command, pipe);
	else if (pid < 0)
		perror("minishell");
	close_unused_in_parent(pipe);
	add_pid(pid);
	free_and_continue(NULL);
}
