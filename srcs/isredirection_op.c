/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isredirection_op.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:41:07 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 00:11:18 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	isredirection_op(t_token *token)
{
	if (token->type == GREAT_TOKEN
		|| token->type == LESS_TOKEN
		|| token->type == DGREAT_TOKEN)
		return (1);
	return (0);
}
