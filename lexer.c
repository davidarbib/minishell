/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:38:40 by darbib            #+#    #+#             */
/*   Updated: 2020/12/01 00:09:31 by darbib           ###   ########.fr       */
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

t_token
match_operator(char *tested_op)
{
	int		i;
	t_token	token;

	i = 0;
	while (i < TOKENS_NB)
	{	
		token = g_seeked_tokens[i];
		printf("tested_op : %s\n", tested_op);
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

	delimited_token.type = fsm->current_token.type;
	delimited_token.value = strdup((const char *)fsm->buf);
	bzero(fsm->buf, fsm->size);
	delimited_token.size = fsm->count;
	lexer->tokens[lexer->count++] = delimited_token;
}

int			test_operator_completion(t_lexer *lexer, t_fsm *fsm, 
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

void		handle_notquoted_char(t_lexer *lexer, t_fsm *fsm, char current_char)
{
	if (is_operator(&fsm->current_token))
	{
		if (test_operator_completion(lexer, fsm, current_char))
			return ;
	}
	if (check_quoting_char(fsm, current_char))
		return ;
	if (check_substitution_mark(fsm, current_char))
		return ;
	if (check_new_op(lexer, fsm, current_char))
		return ;
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
	//-----tests for match_operator
	char *op = "|";
	t_token token = match_operator(op);
	printf("type of %s : %d\n", op, token.type);
	printf("%d\n", DGREAT_TOKEN);

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
	//-----tests for test_operator_completion
	printf("---------------------\n");
	t_lexer lexer2;
	t_fsm fsm2;

	lexer2.tokens = malloc(sizeof(t_token) * LEXERSIZE);
	lexer2.count = 0;
	lexer2.size = LEXERSIZE;
	fsm2.state = NORMAL_STATE;
	fsm2.current_token.type = GREAT_TOKEN;
	fsm2.current_token.value = ">";
	fsm2.size = 1024;
	bzero(fsm2.buf, fsm2.size);
	memcpy(fsm2.buf, ">", 1);
	fsm2.count = 1;
	printf("completion possible: %d\n", test_operator_completion(&lexer2, &fsm2, '>'));
	printf("token type : %d\n", fsm2.current_token.type); 
	for (size_t i = 0; i < lexer2.size; i++)
	{
		printf("token : %s\n", lexer2.tokens[i].value);
		printf("token type: %u\n", lexer2.tokens[i].type);
	}
	//-----tests check_quoting_char
	printf("---------------------\n");
	t_fsm	fsm3;
	int		ret;
	fsm3.count = 0;
	bzero(fsm3.buf, 1024);
	fsm3.state = NORMAL_STATE;
	ret = check_quoting_char(&fsm3, '\'');
	printf("machine state : %d\nret : %d\n", fsm3.state, ret);
	fsm3.state = NORMAL_STATE;
	ret = check_quoting_char(&fsm3, '\"');
	printf("machine state : %d\nret : %d\n", fsm3.state, ret);
	fsm3.state = NORMAL_STATE;
	ret = check_quoting_char(&fsm3, '\\');
	printf("machine state : %d\nret : %d\n", fsm3.state, ret);
	fsm3.state = NORMAL_STATE;
	ret = check_quoting_char(&fsm3, 'q');
	printf("machine state : %d\nret : %d\n", fsm3.state, ret);
	//-----tests check_substitution_mark
	printf("---------------------\n");
	t_fsm	fsm4;
	int		ret2;
	fsm4.state = NORMAL_STATE;	
	fsm4.count = 0;
	bzero(fsm4.buf, 1024);
	ret2 = check_substitution_mark(&fsm4, '$');
	printf("buffer : %s\nret : %d\n", fsm4.buf, ret2);
	bzero(fsm4.buf, 1024);
	fsm4.count = 0;
	ret2 = check_substitution_mark(&fsm4, 'a');
	printf("buffer : %s\nret : %d\n", fsm4.buf, ret2);
	//-----tests check_new_op
	printf("---------------------\n");
	t_fsm	fsm5;
	int		ret5;
	t_lexer lexer5;
	fsm5.state = NORMAL_STATE;	
	fsm5.count = 0;
	fsm5.current_token.type = WORD_TOKEN;
	fsm5.size = 1024;
	bzero(fsm5.buf, fsm5.size);
	memcpy(fsm5.buf, "ab", 2);
	lexer5.tokens = malloc(sizeof(t_token) * LEXERSIZE);
	bzero(lexer5.tokens, sizeof(t_token) * LEXERSIZE);
	lexer5.count = 0;
	lexer5.size = LEXERSIZE;
	ret5 = check_new_op(&lexer5, &fsm5, '<');
	printf("ret = %d\n", ret5);
	for (size_t i = 0; i < lexer5.size; i++)
	{
		printf("token : %s\n", lexer5.tokens[i].value);
		printf("token type: %u\n", lexer5.tokens[i].type);
	}
	
	//-----tests for test_operator_completion route
	//t_lexer lexer3;
	//t_fsm fsm3;
	//char *input = ">>";

	//lexer2 = analyse_command(input);
	
	//-----tests for analyse_command
	/*
	char *input = ">> ok > \nc'est bien";
	t_lexer lexer = analyse_command(input);
	size_t i = 0;
	while (i < lexer.size)
		printf("token : %s\n", lexer.tokens[i++].value);
	*/
	return (0);
}
