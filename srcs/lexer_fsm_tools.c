/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fsm_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 21:40:12 by darbib            #+#    #+#             */
/*   Updated: 2020/12/05 23:22:50 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>
#include "lexer.h"
#include "libft.h"

void		init_lexer_fsm(t_lexer *lexer, t_fsm *fsm)
{
	lexer->tokens = NULL;
	fsm->buf = NULL;
	lexer->size = LEXERSIZE;
	lexer->count = 0;
	lexer->tokens = malloc(sizeof(t_token) * lexer->size);
	fsm->state = NORMAL_STATE;
	fsm->current_token.type = DUMMY_TOKEN;
	fsm->size = FSMBUFSIZE;
	fsm->buf = ft_calloc(fsm->size, sizeof(char));
	fsm->count = 0;
}

void		add_token(t_lexer *lexer, t_token token, t_fsm *fsm)
{
	size_t	actual_size_bytes;

	if ((size_t)lexer->count == lexer->size)
	{
		actual_size_bytes = lexer->size * sizeof(t_token);
		if (!(lexer->tokens = (t_token *)ft_realloc(lexer->tokens,
								actual_size_bytes, actual_size_bytes * 2)))
		{
			//sys_error_in_lexing(lexer, fsm);
			(void)fsm;
			return ;
		}
		lexer->size *= 2;
	}
	lexer->tokens[lexer->count] = token;
	lexer->count++;
}

void		add_char_to_fsm_buffer(t_fsm *fsm, char c, t_lexer *lexer)
{
	if ((size_t)fsm->count + 1 == fsm->size)
	{
		if (!(fsm->buf = (char *)ft_realloc(fsm->buf, fsm->size, 
											fsm->size * 2)))
		{
			//sys_error_in_lexing(fsm, fsm);
			(void)lexer;
			return ;
		}
		fsm->size *= 2;
	}
	fsm->buf[fsm->count] = c;
	fsm->count++;
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
