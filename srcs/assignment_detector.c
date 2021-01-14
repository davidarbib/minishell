/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_detector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:26:45 by darbib            #+#    #+#             */
/*   Updated: 2021/01/13 14:11:24 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "assignment.h"

static void	init_transitions_tb(unsigned char transitions[STATE_NB][INPUT_NB])
{
	unsigned char c;

	ft_memset(transitions[BASE_STATE], ERROR_STATE, INPUT_NB);
	ft_memset(transitions[ALPHA_STATE], ERROR_STATE, INPUT_NB);
	c = '0';
	while (c <= '9')
		transitions[ALPHA_STATE][c++] = ALPHA_STATE;	
	c = 'A';
	while (c <= 'Z')
	{
		transitions[BASE_STATE][c] = ALPHA_STATE;	
		transitions[ALPHA_STATE][c] = ALPHA_STATE;
		c++;
	}
	c = 'a';
	while (c <= 'z')
	{
		transitions[BASE_STATE][c] = ALPHA_STATE;	
		transitions[ALPHA_STATE][c] = ALPHA_STATE;	
		c++;
	}
	transitions[ALPHA_STATE]['='] = EQUAL_STATE;
	transitions[BASE_STATE]['_'] = ALPHA_STATE;
	transitions[ALPHA_STATE]['_'] = ALPHA_STATE;
	ft_memset(transitions[EQUAL_STATE], EQUAL_STATE, INPUT_NB);
}

#include <stdio.h>
static void	check_word(t_token *token,
						unsigned char transitions[STATE_NB][INPUT_NB])
{
	unsigned char	state;
	int				i;
	
	if (token->type != WORD_TOKEN)
		return ;
	i = 0;
	state = BASE_STATE;
	printf("token size : %zu\n", token->size);
	while ((size_t)i < token->size)
	{
		printf("state : %u\n", state);
		state = transitions[state][(unsigned char)token->value[i]];
		if (state == ERROR_STATE)
			return ;
		i++;
	}
	if (state == EQUAL_STATE)
		token->type = ASSIGNMENT_TOKEN;
}

void		detect_assignment(t_lexer *lexer)
{
	unsigned char	transitions[STATE_NB][INPUT_NB];	
	int				i;

	init_transitions_tb(transitions);
	i = 0;
	while (i < lexer->count)
		check_word(lexer->tokens + i, transitions);
}

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
static void	print_transitions(unsigned char	transitions[STATE_NB][INPUT_NB])
{
	for (int i = 0; i < STATE_NB; i++)
	{
		for (int j = 0; j < INPUT_NB; j++)
		{
			unsigned char c = transitions[i][j] + '0';
			write(1, &c, 1);
		}
		write(1, "\n", 1);
	}
}

int main()
{
	t_token token;
	unsigned char	transitions[STATE_NB][INPUT_NB];	

	init_transitions_tb(transitions); //for UT
	print_transitions(transitions);
	token.type=WORD_TOKEN;
	char *str = "ok=43";
	token.value = str;
	token.size = strlen(str);
	check_word(&token, transitions);
	printf("token value : %s\n", token.value);
	printf("token type : %d\n", token.type);
	printf("------------------------------\n");
	token.type=WORD_TOKEN;
	str = "fdslfkjd";
	token.value = str;
	token.size = strlen(str);
	check_word(&token, transitions);
	printf("token value : %s\n", token.value);
	printf("token type : %d\n", token.type);
	printf("------------------------------\n");
	token.type=WORD_TOKEN;
	str = "=2";
	token.value = str;
	token.size = strlen(str);
	check_word(&token, transitions);
	printf("token value : %s\n", token.value);
	printf("token type : %d\n", token.type);
	printf("------------------------------\n");
	token.type=WORD_TOKEN;
	str = "_=56";
	token.value = str;
	token.size = strlen(str);
	check_word(&token, transitions);
	printf("token value : %s\n", token.value);
	printf("token type : %d\n", token.type);
	printf("------------------------------\n");
	token.type=WORD_TOKEN;
	str = "9=97";
	token.value = str;
	token.size = strlen(str);
	check_word(&token, transitions);
	printf("token value : %s\n", token.value);
	printf("token type : %d\n", token.type);
	printf("------------------------------\n");
	token.type=WORD_TOKEN;
	str = "a=";
	token.value = str;
	token.size = strlen(str);
	check_word(&token, transitions);
	printf("token value : %s\n", token.value);
	printf("token type : %d\n", token.type);
}
*/
