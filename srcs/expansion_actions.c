/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:06:30 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 11:40:16 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_quote_removal.h"
#include <stdio.h>
#include "minishell.h"

int		copy_to_search_buffer(t_expand *fsm)
{
	int success;

	success = add_char_to_buffer(fsm->search_buf, &fsm->search_buf_size,
								&fsm->search_buf_count, fsm->current_char);
	if (!success)
		return (0);
	return (1);
}

int		copy_to_result_buffer(t_expand *fsm)
{
	int success;

	success = add_char_to_buffer(fsm->result_buf, &fsm->result_buf_size,
								&fsm->result_buf_count, fsm->current_char);
	if (!success)
		return (0);
	return (1);
}

int		check_do_escaping(t_expand *fsm)
{
	int	success;

	if (!(fsm->current_char == '"' || fsm->current_char == '$'
		|| fsm->current_char == '\\' || fsm->current_char == '`'))
	{
		success = add_char_to_buffer(fsm->result_buf, &fsm->result_buf_size,
									&fsm->result_buf_count, '\\');
	}
	success = add_char_to_buffer(fsm->result_buf, &fsm->result_buf_size,
								&fsm->result_buf_count, fsm->current_char);
	return (success);
}

int		copy_char_in_search_buffer_and_fetch(t_expand *fsm)
{
	if (!copy_to_search_buffer(fsm))
		return (0);
	if (!fetch_env_var(fsm))
		return (0);
	return (1);
}

int		put_dollar_to_result(t_expand *fsm)
{
	int	success;

	success = add_char_to_buffer(fsm->result_buf, &fsm->result_buf_size,
								&fsm->result_buf_count, '$');
	if (!success)
		return (-1);
	return (1);
}
