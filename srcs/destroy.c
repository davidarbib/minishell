/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 23:19:24 by darbib            #+#    #+#             */
/*   Updated: 2021/01/31 13:28:09 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>

void	destroy_lexer(t_lexer *lexer)
{
	ft_memdel((void **)&lexer->tokens);
}

void	destroy_fsm(t_fsm *fsm)
{
	ft_memdel((void **)&fsm->buf);
}

void	exit_lexing(t_lexer *lexer, t_fsm *fsm)
{
	destroy_lexer(lexer);
	destroy_fsm(fsm);
	perror("Error : ");
	exit(EXIT_FAILURE);
}
