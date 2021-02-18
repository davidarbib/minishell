/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handling_fts.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 11:37:03 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 12:26:16 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>
#include "lexer.h"
#include "libft.h"

int			check_operator_completion(t_lexer *lexer, t_fsm *fsm,
			char current_char)
{
	char	test_op[4];
	t_token	matched_token;

	ft_bzero(test_op, 4);
	ft_memmove(test_op, fsm->current_token.value, fsm->current_token.size);
	test_op[fsm->current_token.size] = current_char;
	matched_token = match_operator(test_op, fsm);
	if (matched_token.type == DUMMY_TOKEN)
	{
		delimit_token(lexer, fsm);
		return (0);
	}
	fsm->current_token = matched_token;
	fsm->buf[fsm->count++] = current_char;
	return (1);
}

int			check_quoting_char(t_fsm *fsm, char current_char)
{
	if (current_char == '\'')
	{
		fsm->state = QUOTE_STATE;
		fsm->buf[fsm->count++] = current_char;
		return (1);
	}
	if (current_char == '\"')
	{
		fsm->state = DQUOTE_STATE;
		fsm->buf[fsm->count++] = current_char;
		return (1);
	}
	if (current_char == '\\')
	{
		fsm->state = ESCAPE_STATE;
		fsm->buf[fsm->count++] = current_char;
		return (1);
	}
	return (0);
}

int			check_substitution_mark(t_fsm *fsm, char current_char)
{
	if (current_char == '$')
	{
		fsm->buf[fsm->count++] = current_char;
		return (1);
	}
	return (0);
}

int			check_new_op(t_lexer *lexer, t_fsm *fsm, char current_char)
{
	char	tested_op[2];
	t_token	matched_token;

	tested_op[0] = current_char;
	tested_op[1] = 0;
	matched_token = match_operator(tested_op);
	if (matched_token.type != DUMMY_TOKEN)
	{
		delimit_token(lexer, fsm);
		fsm->current_token = matched_token;
		fsm->buf[fsm->count++] = current_char;
		return (1);
	}
	return (0);
}

int			check_blank(t_lexer *lexer, t_fsm *fsm, char current_char)
{
	if (current_char != '\n' && isspace(current_char))
	{
		delimit_token(lexer, fsm);
		return (1);
	}
	return (0);
}
