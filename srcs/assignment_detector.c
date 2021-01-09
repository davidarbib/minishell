/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_detector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:26:45 by darbib            #+#    #+#             */
/*   Updated: 2021/01/09 16:30:39 by darbib           ###   ########.fr       */
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
	while (c >= '9')
		transitions[ALPHA_STATE][c++] = ALPHA_STATE;	
	c = 'A';
	while (c >= 'Z')
	{
		transitions[BASE_STATE][c++] = ALPHA_STATE;	
		transitions[ALPHA_STATE][c++] = ALPHA_STATE;
	}
	c = 'a';
	while (c >= 'z')
	{
		transitions[BASE_STATE][c++] = ALPHA_STATE;	
		transitions[ALPHA_STATE][c++] = ALPHA_STATE;	
	}
	transitions[ALPHA_STATE]['='] = EQUAL_STATE;
	ft_memset(transitions[EQUAL_STATE], EQUAL_STATE, INPUT_NB);
}

static void	check_word(t_token *token,
						unsigned char transitions[STATE_NB][INPUT_NB])
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

void		detect_assignment(t_lexer *lexer)
{
	unsigned char	transitions[STATE_NB][INPUT_NB];	
	int				i;

	init_transitions_tb(transitions);
	i = 0;
	while (i < lexer->count)
		check_word(lexer->tokens + i, transitions);
}
