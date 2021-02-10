/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_removal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:26:18 by darbib            #+#    #+#             */
/*   Updated: 2021/02/10 14:56:53 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_QUOTE_REMOVAL_H
# define EXPAND_QUOTE_REMOVAL_H

# define STATE_NB	7
# define INPUT_NB	128

typedef enum	e_expand_fsm
{
	base_state,
	squote_state,
	dquote_state,
	equote_state,
	expand_first_state,
	expand_core_state,
	equote_in_dquote_state
}				t_expand_fsm;

typedef struct	s_expand
{
	char	*expand_buf;
	char	*name_buf;
}				t_expand;

#endif
