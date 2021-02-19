/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_detector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:26:45 by darbib            #+#    #+#             */
/*   Updated: 2021/02/19 10:59:01 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "assignment.h"

void	init_transitions_tb(unsigned char
											transitions[A_STATE_NB][A_INPUT_NB])
{
	unsigned char c;

	ft_memset(transitions[BASE_STATE], ERROR_STATE, A_INPUT_NB);
	ft_memset(transitions[ALPHA_STATE], ERROR_STATE, A_INPUT_NB);
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
	ft_memset(transitions[EQUAL_STATE], EQUAL_STATE, A_INPUT_NB);
}

static void	check_word(t_token *token,
						unsigned char transitions[A_STATE_NB][A_INPUT_NB])
{
	unsigned char	state;
	int				i;

	if (token->type != WORD_TOKEN)
		return ;
	i = 0;
	state = BASE_STATE;
	while ((size_t)i < token->size)
	{
		state = transitions[state][(unsigned char)token->value[i]];
		if (state == ERROR_STATE)
			return ;
		i++;
	}
	if (state == EQUAL_STATE)
		token->type = ASSIGNMENT_TOKEN;
}

void		detect_assignment(t_token *token)
{
	static unsigned char	transitions[A_STATE_NB][A_INPUT_NB];
	static int				filled_table = 0;

	if (!filled_table)
	{
		init_transitions_tb(transitions);
		filled_table = 1;
	}
	check_word(token, transitions);
}

void		detect_assignments(t_lexer *lexer)
{
	int i;

	i = 0;
	while (i < lexer->count)
	{
		detect_assignment(lexer->tokens + i);
		i++;
	}
}
