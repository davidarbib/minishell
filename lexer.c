/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:38:40 by darbib            #+#    #+#             */
/*   Updated: 2020/11/20 21:25:11 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "lexer.h"

t_token		const g_seeked_tokens[TOKENS_NB] = 
{
	{redir_token, ">>", 2},
	{redir_token, ">", 1},
	{redir_token, "<", 1},
	{pipe_token, "|", 1},
	{separator_token, ";", 1},
	{white_token, " ", 1},
	{white_token, "\f", 1},
	{white_token, "\t", 1},
	{white_token, "\n", 1},
	{white_token, "\r", 1},
	{white_token, "\v", 1}
};

size_t		apply_known_patterns(char *command, t_lexer *lexer)
{
	int		i;
	t_token	token;

	i = 0;

	while (i < TOKENS_NB)
	{	
		token = g_seeked_tokens[i];
		if (!(strncmp(token.value, command, token.size)))
		{
			lexer->tokens[lexer->size++] = token;
			return (token.size);
		}
		i++;
	}
	return (0);
}

t_lexer		analyse_command(char *command)
{
	t_lexer		lexer;
	int			i;

	lexer.tokens = malloc(sizeof(t_token) * 32);
	lexer.size = 0;
	i = 0;
	while (command[i])
		i += apply_known_patterns(command + i, &lexer);
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
