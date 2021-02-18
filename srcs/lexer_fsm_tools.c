/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fsm_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 21:40:12 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 00:05:01 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>
#include "lexer.h"
#include "libft.h"

int	init_lexer_fsm(t_lexer *lexer, t_fsm *fsm)
{
	lexer->tokens = NULL;
	lexer->size = LEXERSIZE;
	lexer->count = 0;
	lexer->tokens = (t_token *)ft_calloc(lexer->size, sizeof(t_token));
	lexer->state = OK_STATE;
	fsm->buf = NULL;
	fsm->state = NORMAL_STATE;
	fsm->current_token.type = DUMMY_TOKEN;
	fsm->current_token.value = NULL;
	fsm->size = FSMBUFSIZE;
	fsm->buf = (char *)ft_calloc(fsm->size, sizeof(char));
	fsm->count = 0;
	fsm->seeked_tokens[0] = (t_token){GREAT_TOKEN, ">", 1};
	fsm->seeked_tokens[1] = (t_token){DGREAT_TOKEN, ">>", 2};
	fsm->seeked_tokens[2] = (t_token){LESS_TOKEN, "<", 1};
	fsm->seeked_tokens[3] = (t_token){PIPE_TOKEN, "|", 1};
	fsm->seeked_tokens[4] = (t_token){SCOLON_TOKEN, ";", 1};
	fsm->seeked_tokens[5] = (t_token){NEWLINE_TOKEN, "\n", 1};
	if (fsm->buf && lexer->tokens)
		return (1);
	return (0);
}

int	add_token(t_lexer *lexer, t_token token)
{
	size_t	actual_size_bytes;

	if ((size_t)lexer->count == lexer->size)
	{
		actual_size_bytes = lexer->size * sizeof(t_token);
		lexer->tokens = (t_token *)ft_realloc(lexer->tokens,
				actual_size_bytes, actual_size_bytes * 2);
		if (!lexer->tokens)
			return (0);
		lexer->size *= 2;
	}
	lexer->tokens[lexer->count] = token;
	lexer->count++;
	return (1);
}

int	add_char_to_fsm_buffer(t_fsm *fsm, char c)
{
	if ((size_t)fsm->count + 1 == fsm->size)
	{
		fsm->buf = (char *)ft_realloc(fsm->buf, fsm->size, fsm->size * 2);
		if (!fsm->buf)
			return (0);
		fsm->size *= 2;
	}
	fsm->buf[fsm->count] = c;
	fsm->count++;
	return (1);
}
