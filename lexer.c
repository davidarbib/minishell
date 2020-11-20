/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:38:40 by darbib            #+#    #+#             */
/*   Updated: 2020/11/20 16:36:37 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "lexer.h"

t_lexer		analyse_command(char	*command)
{
	t_lexer		lexer;

	lexer.tokens = malloc(sizeof(t_token) * 3);
	lexer.size = 0;
	while (*command)
	{
		int i = 0;
		while (i < 1)
		{
			if (!(strncmp(g_remarkable_tokens[i].value, command, g_remarkable_tokens[i].size)))
				lexer.tokens[lexer.size++] = g_remarkable_tokens[i];
			i++;
		}
		command++;
	}
	return (lexer);
}

int main()
{
	char *input = ">> ok > c'est bien";

	t_lexer lexer = analyse_command(input);
	size_t i = 0;
	while (i < lexer.size)
		printf("token : %s\n", lexer.tokens[i++].value);
	return (0);
}
