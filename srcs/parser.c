/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 22:56:09 by darbib            #+#    #+#             */
/*   Updated: 2021/01/25 23:06:58 by darbib           ###   ########.fr       */
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
