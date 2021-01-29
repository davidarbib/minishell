/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fsm_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 21:40:12 by darbib            #+#    #+#             */
/*   Updated: 2021/01/29 22:02:29 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>
#include "lexer.h"
#include "libft.h"

int		init_lexer_fsm(t_lexer *lexer, t_fsm *fsm)
{
	lexer->tokens = NULL;
	lexer->size = LEXERSIZE;
	lexer->count = 0;
	lexer->tokens = (t_token *)ft_calloc(lexer->size, sizeof(t_token));
	fsm->buf = NULL;
	fsm->state = NORMAL_STATE;
	fsm->current_token.type = DUMMY_TOKEN;
	fsm->current_token.value = NULL;
	fsm->size = FSMBUFSIZE;
	fsm->buf = (char *)ft_calloc(fsm->size, sizeof(char));
	fsm->count = 0;
	if (fsm->buf && lexer->tokens)
		return (1);
	return (0);
}

int		add_token(t_lexer *lexer, t_token token)
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

int		add_char_to_fsm_buffer(t_fsm *fsm, char c)
{
	if ((size_t)fsm->count + 1 == fsm->size)
	{
		if (!(fsm->buf = (char *)ft_realloc(fsm->buf, fsm->size, 
											fsm->size * 2)))
		if (!fsm->buf)
			return (0);
		fsm->size *= 2;
	}
	fsm->buf[fsm->count] = c;
	fsm->count++;
	return (1);
}

/*
int main()
{
	t_lexer lexer;
	t_fsm fsm;
	t_token token;

	init_lexer_fsm(&lexer, &fsm);
	token.type = WORD_TOKEN;
	token.value = strdup("ok");
	token.size = 2;
	add_token(&lexer, token, &fsm);
	token.type = PIPE_TOKEN;
	token.value = strdup("|");
	token.size = 1;
	add_token(&lexer, token, &fsm);
	for (int i = 0; i < lexer.count; i++)
	{
		printf("token : %s\n", lexer.tokens[i].value);
		printf("token type: %u\n", lexer.tokens[i].type);
	}
	add_char_to_fsm_buffer(&fsm, 'a', &lexer);
	printf("fsm.buf : --%s--\n", fsm.buf);
	add_char_to_fsm_buffer(&fsm, 'b', &lexer);
	printf("fsm.buf : --%s--\n", fsm.buf);
	add_char_to_fsm_buffer(&fsm, 'c', &lexer);
	printf("fsm.buf : --%s--\n", fsm.buf);
}
*/
