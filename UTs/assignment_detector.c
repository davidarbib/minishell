/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_detector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:23:50 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 13:23:51 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/*
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	print_transitions(unsigned char	transitions[A_STATE_NB][A_INPUT_NB])
{
	for (int i = 0; i < A_STATE_NB; i++)
	{
		for (int j = 0; j < A_INPUT_NB; j++)
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
	unsigned char	transitions[A_STATE_NB][A_INPUT_NB];	

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
