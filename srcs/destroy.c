/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 23:19:24 by darbib            #+#    #+#             */
/*   Updated: 2021/06/11 17:29:21 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>
#include "obj_destructor.h"

void	destroy_lexer(t_lexer *lexer)
{
	if (lexer->tokens)
		destroy_tokens(&lexer->tokens, lexer->size);
}

void	destroy_parser(t_llparser *parser)
{
	destroy_tokens(&parser->tokens, parser->tokens_size);
}

void	destroy_fsm(t_fsm *fsm)
{
	ft_memdel((void **)&fsm->buf);
}

void	exit_lexing(t_lexer *lexer, t_fsm *fsm)
{
	destroy_lexer(lexer);
	destroy_fsm(fsm);
}
