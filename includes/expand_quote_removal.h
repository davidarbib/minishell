/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_removal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:26:18 by darbib            #+#    #+#             */
/*   Updated: 2021/02/08 10:47:37 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_QUOTE_REMOVAL_H
# define EXPAND_QUOTE_REMOVAL_H

# define STATE_NB	6
# define INPUT_NB	127

typedef enum	e_expand_fsm
{
	normal,
	squote,
	dquote,
	equote,
	expand_first,
	expand_core
}				t_expand_fsm;

typedef struct	s_expand
{
	char	*expand_buf;
	char	*name_buf;
}				t_expand;

#endif
