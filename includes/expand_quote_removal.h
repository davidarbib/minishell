/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_removal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:26:18 by darbib            #+#    #+#             */
/*   Updated: 2021/02/05 15:59:06 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_QUOTE_REMOVAL_H
# define EXPAND_QUOTE_REMOVAL_H

typedef enum	e_expand_fsm
{
	normal,
	squote,
	dquote,
	equote,
	expand
}				t_expand_fsm;

typedef struct	s_expand
{
	char	*expand_buf;
	char	*name_buf;
}				t_expand;

#endif
