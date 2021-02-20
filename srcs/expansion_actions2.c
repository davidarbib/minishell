/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_actions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:06:30 by darbib            #+#    #+#             */
/*   Updated: 2021/02/20 22:10:51 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_quote_removal.h"
#include <stdio.h>
#include "minishell.h"

int		fetch_and_copy_char_to_result_buffer(t_expand *fsm)
{
	if (!fetch_env_var(fsm))
		return (0);
	if (!copy_to_result_buffer(fsm))
		return (0);
	return (1);
}
