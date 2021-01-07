/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 22:56:09 by darbib            #+#    #+#             */
/*   Updated: 2020/12/26 13:57:01 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

void	eat(t_llparser *parser)
{
	parser->token_idx++;
}

void	accept(t_llparser *parser)
{
}

t_token	read_token(t_llparser *parser)
{
	return (parser->tokens[parser->token_idx]);
}

void	parse_io_file(t_llparser *parser)
{
	t_token current_token;
	
	current_token = read_token(parser);
	if (current_token.type == GREAT_TOKEN
		|| current_token.type == DGREAT_TOKEN
		|| current_token.type == LESS_TOKEN)
	{
		eat(parser);
		if f
	}
}

void	parse_io_redirect(t_llparser *parser)
{
	parse_io_file(parser);
}
