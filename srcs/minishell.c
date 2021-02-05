/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:52:01 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/05 15:16:08 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_unused_in_parent(int pipe_stdin, int pipe_stdout)
{
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
	t_process	*process;

	if (!pipeline)
		return ;
	process = malloc(sizeof(t_process));
	if (pipeline->next)
	{
		pipe(p);
		next_stdin = p[0];
		process->pipe_out = p[1];
	}
	if ((pid = fork()) == 0)
	{
		redirect_and_launch(pipeline, pipe_stdin, p);
		return ;
	}
	else if (pid < 0)
		perror("minishell");
	close_unused_in_parent(pipe_stdin, p[1]);
	process->pid = pid;
	ft_lstadd_back_elem(&g_all_childs, process);
	eval(pipeline->next, next_stdin);
}

void	run_once(t_reader *reader, char *line)
{
	parse(reader, line);
	eval(reader->parser.current_pipeline, -1);
}

int		main(int argc, char **argv)
{
	char		*line;
	int			result;
	t_reader	reader;

	(void)argv;
	if (argc == 1)
	{
		while (1)
		{
			printf("minishell-1.0$ ");
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
			eval(reader.parser.current_pipeline, -1);
			wait_all_childs();
		}
	}
	else	 // for testing
	{
		run_once(&reader, argv[1]);
		wait_all_childs();
	}
	return (0);
}
