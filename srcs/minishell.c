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

/*int	main()
{
	int	pid;
	int	ret_wait;
	int	status;

	pid = fork();
	status = 0;
	if (pid == 0)
	{
		eval(&list);
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
}*/

void	eval2(t_list **command)
{
	char	**tab;
	int		size;

	tab = (char**)ft_lsttotab(*command, 8, &size);
	ft_lstclear(command, del);
	tab[size] = 0;
	if (execve((char*)tab[0], (char*const*)tab, NULL) == -1)
		perror("minishell");
}

int parse(char *line)
{
	t_lexer	lexer;
	t_llparser parser;

	lexer = analyse_command(line);
	detect_ionumber(&lexer);
	detect_assignments(&lexer);
	initialize_parser(&parser, &lexer);
	parse_simple_command(&parser);
	eval2(&(parser.args));
	return (0);
}

int	main(int argc, char **argv)
{
	char	*line;
	int		result;

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
			eval(line);
		}
	}
	else	// for testing
		eval(argv[1]);
}
