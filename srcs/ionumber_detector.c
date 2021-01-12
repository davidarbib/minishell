/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ionumber_detector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:18:23 by darbib            #+#    #+#             */
/*   Updated: 2021/01/12 16:22:50 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "parser.h"

void	detect_ionumber(t_lexer *lexer)
{
	int				i;
	t_token			next_token;
	t_token			*current_token;

	i = 0;
	while (i < lexer->count - 1)
	{
		current_token = lexer->tokens + i;
		next_token = lexer->tokens[i + 1];
		if (ft_isnumber(current_token->value)
				&& isredirection_op(&next_token))
			current_token->type = IONUMBER_TOKEN;
		i++;
	}
}

/*
#include "string.h"
#include <stdio.h>

int main()
{
	t_token tokens[3];
	t_lexer lexer;

	lexer.count = 3;
	lexer.tokens = tokens;
	tokens[0].type = WORD_TOKEN;
	tokens[0].value = strdup("1abc");
	tokens[1].type = WORD_TOKEN;
	tokens[1].value = strdup("1234");
	tokens[2].type = GREAT_TOKEN;
	tokens[2].value = strdup("<");
	printf("redirection : %d\n", isredirection_op(tokens));
	printf("redirection : %d\n", isredirection_op(tokens + 1));
	printf("redirection : %d\n", isredirection_op(tokens + 2));
	detect_ionumber(&lexer);
	printf("tokens[1] type : %d\n", tokens[1].type);
}
*/
