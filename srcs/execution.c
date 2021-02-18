/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:13:29 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/18 12:09:58 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_in_path(char *command)
{
	char		**tab;
	char		**tab_mem;
	char		*concatenated;
	char		*result;
	size_t		l1;
	size_t		l2;
	struct stat	buf;

	tab = ft_split(lookup_value("PATH", g_env), ':');
	tab_mem = tab;
	l2 = ft_strlen(command);
	result = ft_strdup(command);
	while (*tab)
	{
		l1 = ft_strlen(*tab);
		concatenated = malloc(l1 + l2 + 2);
		ft_strlcpy(concatenated, *tab, l1 + 1);
		concatenated[l1] = '/';
		concatenated[l1 + 1] = 0;
		ft_strlcat(concatenated, command, l1 + l2 + 2);
		if (stat(concatenated, &buf) == 0)
		{
			free(result);
			result = malloc(l1 + l2 + 2);
			ft_strlcpy(result, concatenated, l1 + l2 + 2);
			free(concatenated);
			break ;
		}
		free(concatenated);
		tab++;
	}
	free_tab(tab_mem);
	return (result);
}

void	use_pipes(int next_in_pipeline, int pipe_stdin, int p[])
{
	if (pipe_stdin != 0)
	{
		dup2(pipe_stdin, 0);
		close(pipe_stdin);
	}
	if (next_in_pipeline)
	{
		dup2(p[1], 1);
		close(p[1]);
		close(p[0]);
	}
}

void	use_redirections(t_simple_command *simple_command)
{
	int				*fd;
	t_io_redirect	redir;
	t_list			*redir_list;

	redir_list = simple_command->redirections;
	while (redir_list)
	{
		redir = *(t_io_redirect*)redir_list->content;
		fd = malloc(sizeof(int));
		if (redir.type == i_redirect)
		{
			*fd = open(redir.filename, O_RDONLY);
			ft_lstadd_front_elem(&g_open_fds, fd);
			dup2(*fd, redir.io_number == -1 ? 0 : redir.io_number);
		}
		else
		{
			*fd = open(redir.filename, O_WRONLY | O_CREAT
					| (redir.type == oc_redirect ? 0 : O_APPEND), 0644);
			ft_lstadd_front_elem(&g_open_fds, fd);
			dup2(*fd, redir.io_number == -1 ? 1 : redir.io_number);
		}
		redir_list = redir_list->next;
	}
}

void	close_unused_in_parent(int is_next_in_pipeline, int pipe_stdin,
										int pipe_stdout)
{
	if (is_next_in_pipeline)
		close(pipe_stdout);
	if (pipe_stdin != 0)
		close(pipe_stdin);
}

void	launch(t_simple_command *simple_command, int is_next_in_pipeline,
								int pipe_stdin, int p[])
{
	char	**tab;
	int		size;
	char	*file;
	int		pid;
	int		*pid_ptr;

	file = NULL;
	if (!simple_command->args)
		return ;
	tab = (char**)ft_lsttotab(simple_command->args, 8, &size);
	tab[size] = 0;
	if (!is_built_in(simple_command))
		file = find_in_path(tab[0]);
	if ((pid = fork()) == 0)
	{
		/*free_all(NULL, file, NULL);*/
		use_pipes(is_next_in_pipeline, pipe_stdin, p);
		use_redirections(simple_command);
		if (is_built_in(simple_command))
			exit(launch_built_in(simple_command));
		else
		{
			execve(file, (char*const*)tab, NULL);
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror("minishell");
	free(file);
	close_unused_in_parent(is_next_in_pipeline, pipe_stdin, p[1]);
	if (!(pid_ptr = malloc(sizeof(int))))
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	*pid_ptr = pid;
	ft_lstadd_front_elem(&g_all_childs, pid_ptr);
	/*free_all(NULL, file, tab);*/
	free(tab);
}
