/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:45:37 by darbib            #+#    #+#             */
/*   Updated: 2021/01/15 17:14:02 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_io_redirect	*create_redirection()
void	parse_filename(t_llparser *parser, t_io_redirect *redirection)
{
	t_token current_token;

	current_token = read_token(parser);
	if (current_token.type == WORD_TOKEN)
	{
		parser->state = found;
		redirection->filename = ref_token();
		eat(parser);
	}
	else
		parser->state = error;
}

void	parse_io_file(t_llparser *parser, t_io_redirect *redirection)
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
	t_io_redirect	redirection;

	parser->state = base;
	parse_io_file(parser, &redirection);
}
