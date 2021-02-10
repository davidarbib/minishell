/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:52:01 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/10 11:11:22 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdlib.h>

void	close_unused_in_parent(t_pipeline *pipeline, int pipe_stdin,
										int pipe_stdout)
{
	if (pipeline->next)
		close(pipe_stdout);
	if (pipe_stdin != -1)
		close(pipe_stdin);
}

/*
** pipe_stdin = -1 for the first process of stdin
*/

void	eval(t_pipeline *pipeline, int pipe_stdin)
{
	int			pid;
	int			p[2];
	int			next_stdin;
	int			*pid_ptr;

	if (!pipeline)
		return ;
	if (!(pid_ptr = malloc(sizeof(int))))
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	if (pipeline->next)
	{
		pipe(p);
		next_stdin = p[0];
	}
	if ((pid = fork()) == 0)
	{
		redirect_and_launch(pipeline, pipe_stdin, p);
		return ;
	}
	else if (pid < 0)
		perror("minishell");
	close_unused_in_parent(pipeline, pipe_stdin, p[1]);
	*pid_ptr = pid;
	ft_lstadd_front_elem(&g_all_childs, pid_ptr);
	eval(pipeline->next, next_stdin);
}

void	eval_list(t_shell_list *list)
{
	if (!list)
		return ;
	eval(list->content, -1);
	eval_list(list->next);
}

void	run_once(t_reader *reader, char *line)
{
	parse(reader, line);
	eval_list(reader->parser.shell_list);
}

void	free_all(void)
{
	ft_lstclear(&g_open_fds, free);
}

void	process_env(char **env)
{
	t_assignment	*assignment;
	char			*key;
	char			*value;
	int				i;
	int				j;

	while (*env)
	{
		assignment = malloc(sizeof(t_assignment));
		i = 0;
		while ((*env)[i] != '=')
			i++;
		key = malloc(i + 1);
		ft_strlcpy(key, *env, i + 1);
		assignment->key = key;
		i++;
		j = 0;
		while ((*env)[i + j])
			j++;
		value = malloc(j + 1);
		ft_strlcpy(value, *env + i, j + 1);
		assignment->value = value;
		ft_lstadd_front_elem(&g_env, assignment);
		env++;
	}
}

void	main_loop();

void	signal_handler(int signal)
{
	t_list	*tmp;

	tmp = g_all_childs;
	if (!tmp)
	{
		write(1, FONT_BOLDBLUE "\nminishell-1.0$ " FONT_RESET, 27);
		return ;
	}
	while (tmp)
	{
		kill(*(int*)tmp->content, signal);
		tmp = tmp->next;
	}
	if (signal != SIGINT)
		printf("Quit: %d", signal);
	printf("\n");
}

void	main_loop()
{
	char			*line;
	int				result;
	t_reader		reader;

	write(1, FONT_BOLDBLUE "minishell-1.0$ " FONT_RESET, 26);
	fflush(stdout);
	result = get_next_line(0, &line);
	if (result == -1)
		printf("minishell: error in get_next_line\n");
	else if (result == 0)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	parse(&reader, line);
	eval_list(reader.parser.shell_list);
	wait_all_childs();
	free_all();
}

int		main(int argc, char **argv, char **env)
{
	t_reader		reader;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	process_env(env);
	if (argc == 1)
	{
		while (1)
			main_loop();
	}
	else	 // for testing
	{
		run_once(&reader, argv[1]);
		wait_all_childs();
		free_all();
	}
	return (0);
}
