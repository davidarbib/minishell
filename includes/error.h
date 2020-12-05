/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 23:55:28 by darbib            #+#    #+#             */
/*   Updated: 2020/12/06 00:09:19 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "lexer.h"

void	sys_error_in_lexing(t_lexer *lexer, t_fsm *fsm);
void	destroy_lexer(t_lexer *lexer);
void	destroy_fsm(t_fsm *fsm);
#endif
