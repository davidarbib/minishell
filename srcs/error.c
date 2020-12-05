/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 23:17:53 by darbib            #+#    #+#             */
/*   Updated: 2020/12/06 00:15:21 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "font_color.h"
#include <stdio.h>

void	sys_error_in_lexing(t_lexer *lexer, t_fsm *fsm)
{
	destroy_fsm(fsm);
	destroy_lexer(lexer);
	perror(FONT_BOLDRED "Error " FONT_RESET);
	exit(EXIT_FAILURE);
}
