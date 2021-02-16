/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:13:29 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/16 10:15:05 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand_quote_removal.h"
#include <sys/types.h>
#include <sys/wait.h>

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
		pid = *(int*)g_all_childs->content;
		waitpid(pid, &status, WUNTRACED);
		if (!g_all_childs->next)
		{
			if (WIFEXITED(status))
				g_last_command_result = WEXITSTATUS(status);
			if (WIFSTOPPED(status))
				g_last_command_result = 128 + WSTOPSIG(status);
		}
		ft_lstdel_first(&g_all_childs, del);
	}
}

void	free_tab(char **tab)
{
	while (*tab)
	{
		free(*tab);
		tab++;
	}
}

char	*find_in_path(char *command)
{
	char		**tab;
	char		**tab_mem;
	char		*concatenated;
	size_t		l1;
	size_t		l2;
	struct stat	buf;

	tab = ft_split(lookup_value("PATH", g_env), ':');
	tab_mem = tab;
	l2 = ft_strlen(command);
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
			free(command);
			command = malloc(l1 + l2 + 2);
			ft_strlcpy(command, concatenated, l1 + l2 + 2);
			free(concatenated);
			break ;
		}
		free(concatenated);
		tab++;
	}
	free_tab(tab_mem);
	return (command);
}

int		is_built_in(t_simple_command *simple_command)
{
	int		ret;
	char	*command;

	command = simple_command->args->content;
	ret = 0;
	if (ft_strcmp(command, "cd") == 0 || ft_strcmp(command, "echo") == 0
		|| ft_strcmp(command, "pwd") == 0 || ft_strcmp(command, "exit") == 0
		|| ft_strcmp(command, "env") == 0)
		ret = 1;
	return (ret);
}

int		launch_built_in(t_simple_command *simple_command)
{
	int					ac;
	char				**tab;
	int					size;
	int					ret;

	ret = 1;
	if (!expand_arguments(simple_command->args))
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	tab = (char**)ft_lsttotab(simple_command->args, 8, &size);
	tab[size] = 0;
	ac = 0;
	while (tab[ac])
		ac++;
	if (ft_strcmp(tab[0], "cd") == 0)
	{
		if (ft_cd(ac, tab, &g_env) < 0)
			ret = 1;
		ret = 0;
	}
	if (ft_strcmp(tab[0], "echo") == 0)
	{
		ft_echo(ac, tab, &g_env);
		ret = 0;
	}
	if (ft_strcmp(tab[0], "pwd") == 0)
	{
		ft_pwd();
		ret = 0;
	}
	if (ft_strcmp(tab[0], "exit") == 0)
	{
		ft_exit(ac, tab, &g_env);
		ret = 0;
	}
	if (ft_strcmp(tab[0], "env") == 0)
	{
		ft_env(ac, tab, &g_env);
		ret = 0;
	}
	free(tab);
	return (ret);
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
			if (redir.type == oc_redirect)
				*fd = open(redir.filename, O_WRONLY | O_CREAT, 0644);
			else
				*fd = open(redir.filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
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
	tab = (char**)ft_lsttotab(simple_command->args, 8, &size);
	tab[size] = 0;
	if (!is_built_in(simple_command))
		file = find_in_path(tab[0]);
	if ((pid = fork()) == 0)
	{
		use_pipes(is_next_in_pipeline, pipe_stdin, p);
		use_redirections(simple_command);
		if (is_built_in(simple_command))
		{
			if (launch_built_in(simple_command) == 0)
				exit(EXIT_SUCCESS);
			exit(EXIT_FAILURE);
		}
		else
		{
			execve(file, (char*const*)tab, NULL);
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror("minishell");
	close_unused_in_parent(is_next_in_pipeline, pipe_stdin, p[1]);
	if (!(pid_ptr = malloc(sizeof(int))))
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	*pid_ptr = pid;
	ft_lstadd_front_elem(&g_all_childs, pid_ptr);
	free(tab);
}
