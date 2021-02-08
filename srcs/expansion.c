/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:23:42 by darbib            #+#    #+#             */
/*   Updated: 2021/02/08 10:56:48 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_quote_removal.h"
#include "libft.h"

void	init_transitions(char transitions[STATE_NB][INPUT_NB])
{
	ft_bzero(transitions, STATE_NB * INPUT_NB);
}

void	init_actions(int (*actions[STATE_NB][INPUT_NB])(t_expand*))
{
	ft_bzero(actions, STATE_NB * INPUT_NB * sizeof(void*));
}

int	expand()
{
	char	transitions[STATE_NB][INPUT_NB];
	int		(*actions[STATE_NB][INPUT_NB])(t_expand*);

	init_transitions(transitions);
	init_actions(actions);
	return (1);
}
