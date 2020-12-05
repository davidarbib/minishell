/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 23:19:24 by darbib            #+#    #+#             */
/*   Updated: 2020/12/05 23:41:55 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	destroy_lexer(t_lexer *lexer)
{
	free(lexer->tokens);
}

void	destroy_fsm(t_fsm *fsm)
{
	free(fsm->buf);
}
