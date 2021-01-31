/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:52:01 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/01/30 14:27:41 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

/*void	del(void *arg)
{
	(void)arg;
}*/

void	launch(t_list *command)
{
	char	**tab;
	int		size;

	tab = (char**)ft_lsttotab(command, 8, &size);
	/*ft_lstclear(command, del);*/
	tab[size] = 0;
	execve((char*)tab[0], (char*const*)tab, NULL);
	perror("minishell");
}

/*
** pipe_stdin = -1 for the first process of stdin
*/

int i = 0;

int		eval(t_pipeline *pipeline, int pipe_stdin, int fd)
{
	(void)pipe_stdin;
	int	pid;
	int p[2];
	int next_stdin;
	(void)next_stdin;
	/*int	ret_wait;*/
	int	status;
	(void)p;
	FILE *file = fdopen(fd, "w");

	fprintf(file, "pass no %d, %s\n", i++, pipeline?"content":"null" );
	if (!pipeline)
		return (0);
	status = 0;
	if (pipeline->next)
	{
		fprintf(file, "creating pipe\n");
		fflush(file);
		pipe(p);
		next_stdin = p[0];
	}
	pid = fork();
	if (pid == 0)
	{
		fprintf(fdopen(fd, "w"), "-- child\n");
		if (pipe_stdin != -1)
		{
			close(0);
			dup(pipe_stdin);
			/*close(pipe_stdin);*/
			fprintf(file, "yo ! %d\n", i);
		}
		if (pipeline->next)
		{
			close(1);
			dup(p[1]);
			/*close(p[1]);*/
		}
		launch(((t_simple_command*)pipeline->content)->args);
		fprintf(file, "-- eochild");
		return (0);
	}
	else if (pid < 0)
		perror("minishell");
	else
	{
		/*close(p[0]);*/
		/*close(p[1]);*/
		eval(pipeline->next, next_stdin, fd);
	}
	return (WEXITSTATUS(status));
}

void	run_once(t_lexer *lexer, t_llparser *parser, char *line, int fd)
{
	parse(lexer, parser, line);
	eval(parser->current_pipeline, -1, fd);
}

void	wait_all_pids(void)
{
	int			status;

	while (1)
	{
		waitpid(-1, &status, WUNTRACED);
		if (WIFEXITED(status) || WIFSIGNALED(status))
			return ;
	}
}

int		main(int argc, char **argv)
{
	char		*line;
	int			result;
	t_lexer		lexer;
	t_llparser	parser;
	int			pid;
	int			fd;

	(void)argv;
	fd = open("toto.txt", O_CREAT | O_WRONLY, 0666);
	pid = 0;
	if (argc == 1)
	{
		while (1)
		{
			printf("minishell-1.0$ ");
			fflush(stdout);
			result = get_next_line(0, &line);
			/*if (result == -1)
				printf("minishell: error in get_next_line\n");
			else if (result == 0)
			{
				printf("exit\n");
				exit(EXIT_SUCCESS);
			}*/
			parse(&lexer, &parser, line);
			eval(parser.current_pipeline, -1, fd);
			wait_all_pids();
		}
	}
	else	 // for testing
	{
		run_once(&lexer, &parser, argv[1], fd);
		wait_all_pids();
	}
	return (0);
}
