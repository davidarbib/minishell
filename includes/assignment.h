/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:09:38 by darbib            #+#    #+#             */
/*   Updated: 2021/01/09 16:03:41 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSIGNMENT_H
# define ASSIGNMENT_H

# define STATE_NB		3
# define INPUT_NB		256

/*
** Automata states
** BASE : waiting for underscore or alpha char
** ALPHA : first char accepted, waiting for underscore, alphanumeric or 'equal'
** EQUAL : 'equal' accepted, waiting for all chars
*/
# define BASE_STATE 	0
# define ALPHA_STATE	1
# define EQUAL_STATE	2
# define ERROR_STATE	3

typedef struct		s_assignment_fsm
{
	unsigned char	state;

}					t_assignment_fsm;
#endif