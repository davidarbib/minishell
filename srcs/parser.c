/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 22:56:09 by darbib            #+#    #+#             */
/*   Updated: 2021/01/15 17:06:54 by darbib           ###   ########.fr       */
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

t_token	*ref_token(t_llparser *parser)
{
	return (&parser->tokens[parser->token_idx]);
}



#include "assignment.h"
void	parse_assignment(t_llparser *parser)
{
	t_token token;

	token = read_token(parser);
	detect_assignment(&token);
	parser->state = base;
	if (token.type == ASSIGNMENT_TOKEN)
	{
		parser->state = found;
		eat(parser);
	}
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
