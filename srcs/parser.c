/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 22:56:09 by darbib            #+#    #+#             */
/*   Updated: 2021/01/14 17:04:44 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

void	eat(t_llparser *parser)
{
	parser->token_idx++;
}

/*
void	accept(t_llparser *parser)
{
}
*/

t_token	read_token(t_llparser *parser)
{
	return (parser->tokens[parser->token_idx]);
}

void	parse_filename(t_llparser *parser)
{
	if (read_token(parser).type == WORD_TOKEN)
	{
		parser->state = found;
		eat(parser);
	}
	else
		parser->state = error;
}

void	parse_io_file(t_llparser *parser)
{
	t_token current_token;
	
	current_token = read_token(parser);
	if (isredirection_op(&current_token))
	{
		eat(parser);
		parse_filename(parser);
	}
}

void	parse_io_redirect(t_llparser *parser)
{
	parser->state = base;
	parse_io_file(parser);
}

void	parse_assignment(t_llparser *parser)
{
	parser->state = base;
	if (read_token(parser).type == ASSIGNMENT_TOKEN)
		parser->state = found;
}

#include <stdio.h>

void	parse_prefix(t_llparser *parser)
{
	printf("parser->state : %d\n", parser->state);
	parse_assignment(parser);
	if (parser->state != found)
		parse_io_redirect(parser);
	if (parser->state == found)
		parse_prefix(parser);
}
