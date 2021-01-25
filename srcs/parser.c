/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 22:56:09 by darbib            #+#    #+#             */
/*   Updated: 2021/01/25 14:21:44 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	eat(t_llparser *parser)
{
	parser->token_idx++;
}

t_token	read_token(t_llparser *parser)
{
	return (parser->tokens[parser->token_idx]);
}

t_token	*ref_token(t_llparser *parser)
{
	return (&parser->tokens[parser->token_idx]);
}

#include <stdio.h>
int	parse_sep(t_llparser *parser)
{
	if (read_token(parser).type == SCOLON_TOKEN)
	{
		eat(parser);
		return (1);
	}
	return (0);
}
/*
int	parse_shell_list(t_llparser *parser)
{
}
*/
