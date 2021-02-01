/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:52:01 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/01/31 20:21:56 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

void	del(void *arg)
{
	free(arg);
}

int		cmp(void *process, void *pid_ref)
{
	return (((t_process*)process)->pid - *(int*)pid_ref);
}

void	launch(t_list *command, int fd)
{
	char	**tab;
	int		size;
	int		debug = 1;

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

int		i = 0;
t_list	*all_childs;

int		eval(t_pipeline *pipeline, int pipe_stdin, int fd)
{
	int	pid;
	int p[2];
	int next_stdin;
	int	status;
	int debug = 1;
	int	*pid_index;
	t_process	*process;

	++i;
	/*if (debug)*/
		/*dprintf(fd, "pass no %d, %s\n", ++i, pipeline?"content":"null" );*/
	if (!pipeline)
		return (0);
	process = malloc(sizeof(t_process));
	status = 0;
	if (pipeline->next)
	{
		pipe(p);
		if (debug)
			dprintf(fd, "creating pipe %d : %d <- %d\n", i, p[0], p[1]);
		next_stdin = p[0];
		process->pipe_out = p[1];
	}
	pid = fork();
	if (pid == 0)
	{
		if (pipe_stdin != -1)
		{
			if (debug)
				dprintf(fd, "-- child %d: redirecting input to fd no %d\n", i, pipe_stdin);
			close(0);
			dup(p[0]);
			dup(pipe_stdin);
			close(pipe_stdin);
		}
		if (pipeline->next)
		{
			close(1);
			dup(p[1]);
			close(p[1]);
			if (debug)
				dprintf(fd, "-- child %d: redirecting output to fd no %d\n", i, p[1]);
		}
		launch(((t_simple_command*)pipeline->content)->args, fd);
		return (0);
	}
	else if (pid < 0)
		perror("minishell");
	/*close(p[0]);*/
	/*close(p[1]);*/
	/*pid_index = malloc(sizeof(int));*/
	/**pid_index = pid;*/
	process->pid = pid;
	ft_lstadd_back_elem(&all_childs, process);
	dprintf(fd, "-- child %d's pid is %d\n", i, pid);
	if (pipeline->next)
	{
		printf("turn\n");
		return (eval(pipeline->next, next_stdin, fd));
	}
	return (pid);
}

int		run_once(t_lexer *lexer, t_llparser *parser, char *line, int fd)
{
	parse(lexer, parser, line);
	return (eval(parser->current_pipeline, -1, fd));
}

void	wait_all_childs()
{
	int			status;
	t_list		*temp;
	int			stopped_pid;

	temp = all_childs;
	printf("initial pids:");
	while (temp)
	{
		printf("%d - ", *((int*)temp->content));
		temp = temp->next;
	}
	printf("\n");
	while (1)
	{
		stopped_pid = waitpid(-1, &status, WUNTRACED);
		ft_lstremove_if(&all_childs, &stopped_pid, cmp, del);
		temp = all_childs;
		printf("now:");
		while (temp)
		{
			printf("%d - ", (t_process*)(temp->content)->pid);
			temp = temp->next;
		}
		printf("\n");
		/*if (WIFEXITED(status) || WIFSIGNALED(status))*/
			/*break ;*/
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
			pid = eval(parser.current_pipeline, -1, fd);
			wait_all_childs();
		}
	}
	else	 // for testing
	{
		pid = run_once(&lexer, &parser, argv[1], fd);
		wait_all_childs();
	}
	return (0);
}
