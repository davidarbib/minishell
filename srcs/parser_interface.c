/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:51:43 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/17 21:35:03 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			initialize_parser(t_reader *reader)
{
	reader->parser.tokens = reader->lexer.tokens;
	reader->parser.token_idx = 0;
	reader->parser.state = base;
	reader->parser.shell_list = NULL;
}

static int		lex(t_reader *reader, char *line)
{
	reader->lexer = analyse_command_wrapper(line);
	if (reader->lexer.state == MULTILINE_STATE)
	{
		printf("Error : multiline not handled\n");
		return (1);
	}
	if (reader->lexer.state == KO_STATE)
	{
		destroy_lexer(&reader->lexer);
		perror("minishell");
		return (-1);
	}
	return (0);
}

static int		parse(t_reader *reader)
{
	initialize_parser(reader);
	parse_shell_list(&reader->parser, &reader->parser.shell_list);
	if (reader->parser.state == no_filename_error)
	{
		printf("minishell : syntax error near redirection token\n");
		return (1);
	}
	if (reader->parser.state == multiline)
	{
		printf("Error : multiline not handled\n");
		return (1);
	}
	if (reader->parser.state == sys_error)
	{
		perror("minishell");
		return (-1);
	}
	return (0);
}

int				lex_parse(t_reader *reader, char *line)
{
	int result;

	result = lex(reader, line);
	if (result)
		return (result);
	detect_ionumber(&reader->lexer);
	result = parse(reader);
	if (result)
		return (result);
	return (0);
}
