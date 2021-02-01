/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:52:01 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/01 20:20:15 by fyusuf-a         ###   ########.fr       */
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

int		i = 0;
t_list	*all_childs;

int		eval(t_pipeline *pipeline, int pipe_stdin)
{
	int	pid;
	int p[2];
	int next_stdin;
	int	status;
	/*int	*pid_index;*/
	t_process	*process;

	if (!pipeline)
		return (0);
	process = malloc(sizeof(t_process));
	status = 0;
	if (pipeline->next)
	{
		pipe(p);
		next_stdin = p[0];
		process->pipe_out = p[1];
	}
	pid = fork();
	if (pid == 0)
	{
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
		launch(((t_simple_command*)pipeline->content)->args);
		return (0);
	}
	else if (pid < 0)
		perror("minishell");
	close(p[1]);
	if (pipe_stdin != -1)
		close(pipe_stdin);
	process->pid = pid;
	ft_lstadd_back_elem(&all_childs, process);
	if (pipeline->next)
	{
		return (eval(pipeline->next, next_stdin));
	}
	return (pid);
}

int		run_once(t_reader *reader, char *line)
{
	parse(reader, line);
	return (eval(reader->parser.current_pipeline, -1));
}

void	wait_all_childs()
{
	int			status;
	t_list		*temp;
	int			stopped_pid;
	t_process	*process;

	temp = all_childs;
	while (1)
	{
		stopped_pid = waitpid(-1, &status, WUNTRACED);
		process = ft_lstfind_content(all_childs, &stopped_pid, cmp);
		ft_lstremove_if(&all_childs, &stopped_pid, cmp, del);
		temp = all_childs;
		if (temp)
			break;
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

	(void)argv;
	remove("toto.txt");
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
			pid = eval(reader.parser.current_pipeline, -1);
			wait_all_childs();
		}
	}
	else	 // for testing
	{
		pid = run_once(&reader, argv[1]);
		wait_all_childs();
	}
	return (0);
}
