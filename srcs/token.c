/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 21:23:40 by darbib            #+#    #+#             */
/*   Updated: 2021/01/29 22:07:37 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>
#include <lexer.h>
#include "libft.h"

extern	t_token g_seeked_tokens[TOKENS_NB];

int		is_operator(t_token *token)
{
	if (token->type >= PIPE_TOKEN)
		return (1);
	return (0);
}

t_token		match_operator(char *tested_op)
{
	int		i;
	t_token	token;

	i = 0;
	while (i < TOKENS_NB)
	{	
		token = g_seeked_tokens[i];
//		printf("tested_op : %s\n", tested_op);
		if (strstr(token.value, tested_op))
			return (token);
		i++;
	}
	token.type = DUMMY_TOKEN;
	return (token);
}

void		delimit_token(t_lexer *lexer, t_fsm *fsm)
{
	t_token		delimited_token;

	if (fsm->current_token.type == DUMMY_TOKEN)
		return ;
	delimited_token.type = fsm->current_token.type;
	delimited_token.value = ft_strdup((const char *)fsm->buf);
	bzero(fsm->buf, fsm->size);
	delimited_token.size = fsm->count;
	lexer->tokens[lexer->count++] = delimited_token;
	//use add token
	fsm->count = 0;
	fsm->current_token.type = DUMMY_TOKEN;
}

/*
int main()
{
	//-----tests for match_operator
	char *op = "|";
	t_token token = match_operator(op);
	printf("type of %s : %d\n", op, token.type);
	printf("%d\n", DGREAT_TOKEN);
	
	//-----tests for is_operator
	token.type = GREAT_TOKEN;
	printf("great is an operator : %d\n", is_operator(&token));
	token.type = DUMMY_TOKEN;
	printf("dummy is an operator : %d\n", is_operator(&token));
	token.type = PIPE_TOKEN;
	printf("pipe is an operator : %d\n", is_operator(&token));
	token.type = TEXT_TOKEN;
	printf("text is an operator : %d\n", is_operator(&token));

	//-----tests for delimit_token
	printf("---------------------\n");
#define LEXERSIZE 3
	t_lexer lexer;
	t_fsm fsm;

	lexer.tokens = malloc(sizeof(t_token) * LEXERSIZE);
	lexer.count = 0;
	lexer.size = LEXERSIZE;
	fsm.state = NORMAL_STATE;
	fsm.current_token.type = SCOLON_TOKEN;
	memcpy(fsm.buf, ";", 1);
	fsm.count = 1;
	fsm.size = 1024;
	delimit_token(&lexer, &fsm);
	
	fsm.current_token.type = PIPE_TOKEN;
	memcpy(fsm.buf, "|", 1);
	fsm.count = 1;
	delimit_token(&lexer, &fsm);

	fsm.current_token.type = DGREAT_TOKEN;
	memcpy(fsm.buf, ">>", 2);
	fsm.count = 1;
	delimit_token(&lexer, &fsm);
	for (size_t i = 0; i < lexer.size; i++)
	{
		printf("token : %s\n", lexer.tokens[i].value);
		printf("token type: %u\n", lexer.tokens[i].type);
	}
}
*/
