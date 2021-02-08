/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:13:29 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/08 18:39:57 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		pid = ((t_process*)g_all_childs->content)->pid;
		waitpid(pid, &status, WUNTRACED);
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

void	maybe_launch_built_in(char **tab)
{
	int	ac;

	ac = 0;
	while (tab[ac])
		ac++;
	if (ft_strcmp(tab[0], "cd") == 0)
	{
		/*printf("executing cd...\n");*/
		if (ft_cd(ac, tab, &g_env) < 0)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	if (ft_strcmp(tab[0], "echo") == 0)
	{
		/*printf("executing echo...\n");*/
		ft_echo(ac, tab, &g_env);
	}
	if (ft_strcmp(tab[0], "pwd") == 0)
		ft_pwd();
}

void	launch(t_list *command)
{
	char	**tab;
	int		size;
	char	*file;

	tab = (char**)ft_lsttotab(command, 8, &size);
	/*ft_lstclear(command, del);*/
	tab[size] = 0;
	maybe_launch_built_in(tab);
	file = find_in_path(tab[0]);
	/*printf("executing %s...\n", file);*/
	execve(file, (char*const*)tab, NULL);
	perror("minishell");
	exit(EXIT_FAILURE);
}

void	redirect_and_launch(t_pipeline *pipeline,int pipe_stdin,
									int p[])
{
	t_simple_command	command;
	t_list				*redir_list;
	t_io_redirect		redir;
	int					*fd;

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
	redir_list = command.redirections;
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
	launch(command.args);
}
