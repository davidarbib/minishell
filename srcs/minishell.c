/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:52:01 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/01/31 13:58:07 by fyusuf-a         ###   ########.fr       */
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

void	launch(t_list *command, int fd)
{
	char	**tab;
	int		size;
	int		debug = 0;

	tab = (char**)ft_lsttotab(command, 8, &size);
	/*ft_lstclear(command, del);*/
	tab[size] = 0;
	if (debug)
		dprintf(fd, "-> %s\n", tab[0]);
	execve((char*)tab[0], (char*const*)tab, NULL);
	perror("minishell");
}

/*
** pipe_stdin = -1 for the first process of stdin
*/

int i = 0;

int		eval(t_pipeline *pipeline, int pipe_stdin, int fd)
{
	int	pid;
	int p[2];
	int next_stdin;
	int	status;
	int debug = 1;

	++i;
	/*if (debug)*/
		/*dprintf(fd, "pass no %d, %s\n", ++i, pipeline?"content":"null" );*/
	if (!pipeline)
		return (0);
	status = 0;
	if (pipeline->next)
	{
		pipe(p);
		if (debug)
			dprintf(fd, "creating pipe %d : %d <- %d\n", i, p[0], p[1]);
			/*dprintf(fd, "creating pipe %d : %d <- %d (%p <- %p)\n", i, p[0], p[1], fdopen(p[0], "r"), fdopen(p[1], "a"));*/
		next_stdin = p[0];
	}
	pid = fork();
	if (pid == 0)
	{
		if (pipe_stdin != -1)
		{
			if (debug)
				dprintf(fd, "-- child %d: redirecting input to fd no %d\n", i, pipe_stdin);
				/*dprintf(fd, "-- child %d: redirecting input to fd no %d (%p)\n", i, pipe_stdin, fdopen(p[0], "r"));*/
			close(0);
			dup(p[0]);
			dup(pipe_stdin);
			close(pipe_stdin);
		}
		if (pipeline->next)
		{
			/*dup2(p[1], 1);*/
			close(1);
			dup(p[1]);
			/*close(p[1]);*/
			if (debug)
				dprintf(fd, "-- child %d: redirecting output to fd no %d\n", i, p[1]);
				/*dprintf(fd, "-- child %d: redirecting output to fd no %d(%p)\n", i, p[1], fdopen(1, "a"));*/
			/*close(p[1]);*/
		}
		dprintf(fd, "-- child %d:\n"
					"             stdin = %p\n"
					"             stout = %p\n", i, fdopen(0, "r"), fdopen(1, "w"));
		/*launch(((t_simple_command*)pipeline->content)->args, fd);*/
		return (0);
	}
	else if (pid < 0)
		perror("minishell");
	else
	{
		/*close(p[1]);*/
		/*if (!(pipeline->next))
		{
			dprintf(fd, "parent (%d): redirecting output to fd no %d\n", i, p[1]);
			close(1);
			dup(p[1]);
		}*/
			/*dup2(1, p[0]);*/
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
	remove("toto.txt");
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
		dprintf(fd, "-- parent :\n"
					"             stdin = %p\n"
					"             stout = %p\n", stdin, stdout);
		dprintf(fd, "-- parent :\n"
					"             stdin = %p\n"
					"             stout = %p\n", fdopen(0, "r"), fdopen(1, "w"));
		run_once(&lexer, &parser, argv[1], fd);
		wait_all_pids();
	}
	return (0);
}
