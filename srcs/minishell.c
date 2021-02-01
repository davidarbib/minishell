/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:52:01 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/01 20:14:15 by fyusuf-a         ###   ########.fr       */
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
	int		debug = 0;

	tab = (char**)ft_lsttotab(command, 8, &size);
	/*ft_lstclear(command, del);*/
	tab[size] = 0;
	if (debug)
		dprintf(fd, "-> %s\n", tab[0]);
	execve((char*)tab[0], (char*const*)tab, NULL);
	perror("minishell");
	/*pause();*/
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
	/*int	*pid_index;*/
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
			dup2(pipe_stdin, 0);
			close(pipe_stdin);
			dprintf(fd, "child %d: closing %d\n", i, pipe_stdin); 
		}
		if (pipeline->next)
		{
			dprintf(fd, "child %d: closing %d\n", i, p[1]); 
			dup2(p[1], 1);
			close(p[1]);
			if (debug)
				dprintf(fd, "-- child %d: redirecting output to fd no %d\n", i, p[1]);
			close(p[0]);
		}
		dprintf(fd, "child %d: closing %d\n", i, p[0]); 
		launch(((t_simple_command*)pipeline->content)->args, fd);
		return (0);
	}
	else if (pid < 0)
		perror("minishell");
	close(p[1]);
	if (pipe_stdin != -1)
		close(pipe_stdin);
	process->pid = pid;
	ft_lstadd_back_elem(&all_childs, process);
	if (debug)
		dprintf(fd, "-- child %d's pid is %d\n", i, pid);
	if (pipeline->next)
	{
		if (debug)
			dprintf(fd, "parent %d: giving %d as stdin for next child\n", i, next_stdin);
		return (eval(pipeline->next, next_stdin, fd));
	}
	return (pid);
}

int		run_once(t_reader *reader, char *line, int fd)
{
	parse(reader, line);
	return (eval(reader->parser.current_pipeline, -1, fd));
}

void	wait_all_childs(int pid, int fd)
{
	(void)pid;
	int			status;
	t_list		*temp;
	int			stopped_pid;
	t_process	*process;
	int			debug = 1;

	temp = all_childs;
	if (debug)
	{
		printf("initial pids:");
		while (temp)
		{
			printf("%d - ", *((int*)temp->content));
			temp = temp->next;
		}
		printf("\n");
	}
	while (1)
	{
		stopped_pid = waitpid(-1, &status, WUNTRACED);
		process = ft_lstfind_content(all_childs, &stopped_pid, cmp);
		if (debug)
			dprintf(fd, "closing fd %d of process %d\n", process->pipe_out, stopped_pid);
		ft_lstremove_if(&all_childs, &stopped_pid, cmp, del);
		temp = all_childs;
		if (debug)
		{
			printf("now:");
			if (!temp)
			{
				printf("nothing\n");
				break;
			}
			while (temp)
			{
				printf("%d - ", ((t_process*)(temp->content))->pid);
				temp = temp->next;
			}
			printf("\n");
		}
		/*if (WIFEXITED(status) || WIFSIGNALED(status))*/
			/*break ;*/
	}
}

int		main(int argc, char **argv)
{
	char		*line;
	int			result;
	t_reader	reader;
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
			parse(&reader, line);
			pid = eval(reader.parser.current_pipeline, -1, fd);
			wait_all_childs(pid, fd);
		}
	}
	else	 // for testing
	{
		pid = run_once(&reader, argv[1], fd);
		wait_all_childs(pid, fd);
	}
	return (0);
}
