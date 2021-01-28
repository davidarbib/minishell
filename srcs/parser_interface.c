/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:51:43 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/01/28 11:06:11 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_parser(t_llparser *parser, t_lexer *lexer)
{
	parser->tokens = lexer->tokens;
	parser->token_idx = 0;
	parser->state = base;
	parser->current_pipeline = NULL;
}

int		parse(t_lexer *lexer, t_llparser *parser, char *line)
{
	*lexer = analyse_command(line);
	detect_ionumber(lexer);
	detect_assignments(lexer);
	initialize_parser(parser, lexer);
	parse_pipeline(parser, &parser->current_pipeline);
	return (0);
}
