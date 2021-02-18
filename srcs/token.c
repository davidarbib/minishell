/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 21:23:40 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 11:18:52 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>
#include <lexer.h>
#include "libft.h"

int		is_operator(t_token *token)
{
	if (token->type >= PIPE_TOKEN)
		return (1);
	return (0);
}

t_token	match_operator(char *tested_op, t_fsm *fsm)
{
	int		i;
	t_token	token;

	i = 0;
	while (i < TOKENS_NB)
	{
		token = fsm->seeked_tokens[i];
		if (strstr(token.value, tested_op))
			return (token);
		i++;
	}
	token.type = DUMMY_TOKEN;
	return (token);
}

int		delimit_token(t_lexer *lexer, t_fsm *fsm)
{
	t_token		delimited_token;
	int			success;

	if (fsm->current_token.type == DUMMY_TOKEN)
		return (1);
	delimited_token.type = fsm->current_token.type;
	delimited_token.value = ft_strdup((const char *)fsm->buf);
	bzero(fsm->buf, fsm->size);
	delimited_token.size = fsm->count;
	success = add_token(lexer, delimited_token);
	if (!success)
		return (0);
	fsm->count = 0;
	fsm->current_token.type = DUMMY_TOKEN;
	return (1);
}
