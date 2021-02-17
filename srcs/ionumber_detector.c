/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ionumber_detector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:18:23 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 00:12:44 by darbib           ###   ########.fr       */
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
