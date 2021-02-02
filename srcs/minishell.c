/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:52:01 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/01/28 15:47:26 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <unistd.h>

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

int		eval(t_pipeline *pipeline, int pipe_stdin)
{
	int	pid;
	int p[2];
	int next_stdin;
	int	ret_wait;
	int	status;

	if (!pipeline)
		return (0);
	pid = fork();
	status = 0;
	if (pipeline->next)
	{
		pipe(p);
		next_stdin = p[0];
	}
	if (pid == 0)
	{
		if (pipe_stdin != -1)
		{
			close(0);
			dup(pipe_stdin);
			close(pipe_stdin);
		}
		if (pipeline->next)
		{
			close(1);
			dup(pipe[1]);
			close(pipe[1]);
		}
		launch(((t_simple_command*)pipeline->content)->args);
		return (0);
	}
	else if (pid < 0)
		perror("minishell");
	else
	{
		close(pipe[1]);
		eval(pipeline->next, next_stdin);
		while (1)
		{
			if ((ret_wait = waitpid(pid, &status, WUNTRACED)) == -1)
			{
				perror("minishell"); // Voir si EINTR est une erreur qui peut avoir lieu ou pas
				continue;
			}
			if (WIFEXITED(status) || WIFSIGNALED(status))
				break ;
		}
	}
	return (WEXITSTATUS(status));
}

void	run_once(t_lexer *lexer, t_llparser *parser, char *line)
{
	parse(lexer, parser, line);
	eval(parser->current_pipeline);
}

int		main(int argc, char **argv)
{
	char		*line;
	int			result;
	t_lexer		lexer;
	t_llparser	parser;

	(void)argv;
	if (argc == 1)
	{
		while (1)
		{
			printf("minishell-1.0$ ");
			fflush(stdout);
			result = get_next_line(0, &line);
			if (result == -1)
				printf("minishell: error in get_next_line");
			else if (result == 0)
			{
				printf("exit\n");
				exit(EXIT_SUCCESS);
			}
			parse(&lexer, &parser, line);
			eval(parser.current_pipeline);
		}
	}
	else	 // for testing
		run_once(&lexer, &parser, argv[1]);
}
