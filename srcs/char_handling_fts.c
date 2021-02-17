/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handling_fts.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 11:37:03 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 00:24:21 by darbib           ###   ########.fr       */
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

/*
int main()
{
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
	ret5 = check_new_op(&lexer5, &fsm5, '>');
	printf("ret = %d\n", ret5);
	for (size_t i = 0; i < lexer5.size; i++)
	{
		printf("token : %s\n", lexer5.tokens[i].value);
		printf("token type: %u\n", lexer5.tokens[i].type);
	}
	printf("fsm buffer : %s\n", fsm5.buf);
	//-----tests for check_operator_completion
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
	printf("completion possible: %d\n", check_operator_completion(&lexer2, &fsm2, '>'));
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
	//-----tests check_blank
	printf("---------------------\n");
	t_fsm	fsm6;
	t_lexer lexer6;
	fsm6.state = NORMAL_STATE;	
	fsm6.count = 0;
	fsm6.current_token.type = WORD_TOKEN;
	fsm6.size = 1024;
	bzero(fsm6.buf, fsm6.size);
	memcpy(fsm6.buf, "ab", 2);
	lexer6.tokens = malloc(sizeof(t_token) * LEXERSIZE);
	bzero(lexer6.tokens, sizeof(t_token) * LEXERSIZE);
	lexer6.count = 0;
	lexer6.size = LEXERSIZE;
	check_blank(&lexer6, &fsm6, '\t');
	for (size_t i = 0; i < lexer6.size; i++)
	{
		printf("token : %s\n", lexer6.tokens[i].value);
		printf("token type: %u\n", lexer6.tokens[i].type);
	}
	printf("fsm buffer : %s\n", fsm6.buf);
}
*/
