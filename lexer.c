/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:38:40 by darbib            #+#    #+#             */
/*   Updated: 2020/11/26 02:10:25 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include "lexer.h"

t_token		const g_seeked_tokens[TOKENS_NB] = 
{
	{DGREAT_TOKEN, ">>", 2},
	{GREAT_TOKEN, ">", 1},
	{LESS_TOKEN, "<", 1},
	{PIPE_TOKEN, "|", 1},
	{SCOLON_TOKEN, ";", 1},
	{NEWLINE_TOKEN, "\n", 1}
};

/*
void		fsm_flush(t_lexer *lexer, t_fsm *fsm)
{	
	t_token		word_token;
	
	word_token.type = WORD_TOKEN;
	word_token.value = strdup(fsm->buf);
	word_token.size = fsm->size;
	lexer->tokens[lexer->size++] = word_token;
}
*/


t_token		match_operator(char *tested_op)
{
	int		i;
	t_token	token;

	i = 0;
	while (i < TOKENS_NB)
	{	
		token = g_seeked_tokens[i];
		if (!(strstr(token.value, tested_op)))
			return (token);
		i++;
	}
	token.type = DUMMY_TOKEN;
	return (token);
}


void		test_operator_completion(t_lexer *lexer, t_fsm *fsm, 
			char current_char)
{
	char	test_op[2];
	t_token	matched_token;

	test_op[0] = fsm->buf[fsm->count];
	test_op[1] = current_char;
	if (!(strstr(fsm->current_token.value, test_op)))
		matched_token = match_operator(test_op);
}

void		handle_notquoted_char(t_lexer *lexer, t_fsm *fsm, char current_char)
{

	if (is_operator(&fsm->current_token))
		test_operator_completion(lexer, fsm, current_char);
	//2
	//3
	//4
	//5
	//6
	//7
}

void		init_lexer_fsm(t_lexer *lexer, t_fsm *fsm)
{
	lexer->tokens = malloc(sizeof(t_token) * 32);
	lexer->size = 0;
	fsm->state = NORMAL_STATE;
	fsm->current_token.type = DUMMY_TOKEN;
	fsm->size = 1024;
	bzero(fsm->buf, fsm->size);
	fsm->count = 0;
}

t_lexer		analyse_command(char *command)
{
	t_lexer		lexer;
	t_fsm		fsm;
	int			i;

	init_lexer_fsm(&lexer, &fsm);
	i = 0;
	while (command[i])
	{
		if (fsm.state == NORMAL_STATE)
			handle_notquoted_char(&lexer, &fsm, command[i]);
	}
	return (lexer);
}


int main()
{
	char *input = ">> ok > \nc'est bien";

	t_lexer lexer = analyse_command(input);
	size_t i = 0;
	while (i < lexer.size)
		printf("token : %s\n", lexer.tokens[i++].value);
	return (0);
}
