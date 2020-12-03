/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handling_fts.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 11:37:03 by darbib            #+#    #+#             */
/*   Updated: 2020/12/03 11:41:48 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>
#include "lexer.h"

int			check_operator_completion(t_lexer *lexer, t_fsm *fsm, 
			char current_char)
{
	char	test_op[3];
	t_token	matched_token;

	test_op[0] = fsm->buf[fsm->count - 1];
	test_op[1] = current_char;
	test_op[2] = 0;
	if (!(strstr(fsm->current_token.value, test_op)))
	{
		matched_token = match_operator(test_op);
		if (matched_token.type == DUMMY_TOKEN)
		{
			delimit_token(lexer, fsm);
			return (0);
		}
		fsm->current_token = matched_token;
	}
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

void		check_blank(t_lexer *lexer, t_fsm *fsm, char current_char)
{
	if (current_char != '\n' && isspace(current_char))
		delimit_token(lexer, fsm);
}
