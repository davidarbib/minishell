/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_destructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 23:41:19 by darbib            #+#    #+#             */
/*   Updated: 2021/02/17 23:44:47 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void	destroy_token_value(t_token *token)
{
	ft_memdel((void **)&token->value);
}

void	destroy_tokens(t_token **tokens, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		destroy_token_value(*tokens + i);
		i++;
	}
	ft_memdel((void **)tokens);
}
