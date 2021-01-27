#include "minishell.h"
#include <sys/wait.h>
#include <unistd.h>

void	del(void *arg)
{
	(void)arg;
}

void	initialize_parser(t_llparser *parser, t_lexer *lexer)
{
	parser->tokens = lexer->tokens;
	parser->token_idx = 0;
	parser->state = base;
	parser->redirections = NULL;
	parser->assignments = NULL;
	parser->args = NULL;
}

void	launch(t_list **command)
{
	char	**tab;
	int		size;

	tab = (char**)ft_lsttotab(*command, 8, &size);
	ft_lstclear(command, del);
	tab[size] = 0;
	execve((char*)tab[0], (char*const*)tab, NULL);
	perror("minishell");
}

int		eval(t_list **command)
{
	int	pid;
	int	ret_wait;
	int	status;

	pid = fork();
	status = 0;
	if (pid == 0)
	{
		launch(command);
		return (0);
	}
	else if (pid < 0)
		perror("minishell");
	else
	{
		while (1)
		{
			if ((ret_wait = waitpid(-1, &status, WUNTRACED)) == -1)
			{
				perror("minishell"); // Voir si EINTR est une erreur qui peut avoir lieu ou pas
				continue;
			}
			if (WIFEXITED(status) || WIFSIGNALED(status))
				break ;
		}
	}
	return (0);
}

int		parse(t_lexer *lexer, t_llparser *parser, char *line)
{
	*lexer = analyse_command(line);
	detect_ionumber(lexer);
	detect_assignments(lexer);
	initialize_parser(parser, lexer);
	parse_simple_command(parser);
	return (0);
}

void	run_once(t_lexer *lexer, t_llparser *parser, char *line)
{
	parse(lexer, parser, line);
	eval(&parser->args);
}

int		main(int argc, char **argv)
{
	char		*line;
	int			result;
	t_lexer		lexer;
	t_llparser	parser;

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
			eval(&parser.args);
		}
	}
	else	// for testing
		run_once(&lexer, &parser, argv[1]);
}
