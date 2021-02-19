/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:13:29 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/19 13:38:30 by fyusuf-a         ###   ########.fr       */
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

void	use_redirections(void)
{
	int in;
	int out;

	in = ((t_redirection*)g_temp_redirections->content)->in;
	out = ((t_redirection*)g_temp_redirections->content)->out;
	if (in != 0)
		dup2(in, 0);
	if (out != 1)
		dup2(out, 1);
	g_temp_redirections = g_temp_redirections->next;
}

void	set_redirections(t_pipeline *pipeline)
{
	t_io_redirect	redir;
	t_list			*redir_list;
	t_redirection	*redirection;
	int				*fd;

	if (!pipeline)
		return ;
	redir_list = ((t_simple_command*)pipeline->content)->redirections;
	if (!(fd = malloc(sizeof(int))))
		exit(EXIT_FAILURE);
	redirection = malloc(sizeof(t_redirection));
	redirection->in = 0;
	redirection->out = 1;
	while (redir_list)
	{
		redir = *(t_io_redirect*)redir_list->content;
		if (redir.type == i_redirect)
		{
			if (redirection->in != 0)
				close(redirection->in);
			if ((redirection->in = open(redir.filename, O_RDONLY)) < 0)
				exit(EXIT_FAILURE);
		}
		else
		{
			if (redirection->out != 1)
				close(redirection->out);
			if ((redirection->out =
					open(redir.filename, O_WRONLY | O_CREAT |
					(redir.type == oc_redirect ? 0 : O_APPEND), 0644)) < 0)
				exit(EXIT_FAILURE);
		}
		redir_list = redir_list->next;
	}
	ft_lstadd_back_elem(&g_redirections, redirection);
	set_redirections(pipeline->next);
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
	char	**env;
	int		size;
	char	*file;
	int		pid;
	int		*pid_ptr;

	file = NULL;
	if (!simple_command->args)
		return ;
	tab = (char**)ft_lsttotab(simple_command->args, 8, &size);
	env = to_environ_array(g_env);
	tab[size] = 0;
	if (!is_built_in(simple_command))
		file = find_in_path(tab[0]);
	if (!file)
	{
		free_tab(env);
		free(tab);
		g_last_command_result = 127;
		perror("minishell");
		return ;
	}
	if ((pid = fork()) == 0)
	{
		/*free_all(NULL, file, NULL);*/
		use_pipes(is_next_in_pipeline, pipe_stdin, p);
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
	free_tab(env);
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
