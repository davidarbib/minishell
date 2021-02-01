/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:51:43 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/01 19:57:12 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_parser(t_reader *reader)
{
	reader->parser.tokens = reader->lexer.tokens;
	reader->parser.token_idx = 0;
	reader->parser.state = base;
	reader->parser.current_pipeline = NULL;
}

int		parse(t_reader *reader, char *line)
{
	reader->lexer = analyse_command(line);
	detect_ionumber(&reader->lexer);
	detect_assignments(&reader->lexer);
	initialize_parser(reader);
	parse_pipeline(&reader->parser, &reader->parser.current_pipeline);
	return (0);
}
