/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:58:04 by darbib            #+#    #+#             */
/*   Updated: 2020/11/26 01:56:55 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

int		is_operator(t_token *token)
{
	if (token->type >= PIPE_TOKEN)
		return (1);
	return (0);
}

int main()
{
	t_token token;

	token.type = GREAT_TOKEN;
	printf("great is an operator : %d\n", is_operator(&token));
	token.type = DUMMY_TOKEN;
	printf("dummy is an operator : %d\n", is_operator(&token));
	token.type = PIPE_TOKEN;
	printf("pipe is an operator : %d\n", is_operator(&token));
	token.type = TEXT_TOKEN;
	printf("text is an operator : %d\n", is_operator(&token));
}
