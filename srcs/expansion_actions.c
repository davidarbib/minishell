/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:06:30 by darbib            #+#    #+#             */
/*   Updated: 2021/02/11 23:17:45 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_quote_removal.h"

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
	(void)fsm;
	return (1);
}

int	fetch_special_var(t_expand *fsm)
{
	int		success;

	if (fsm->search_buf_count == 0)
	{
		success = add_char_to_buffer(fsm->result_buf, &fsm->result_buf_size, 
								&fsm->result_buf_count, '$');
		if (!success)
			return (-1);
		return (1);
	}
	if (fsm->search_buf[0] == '?')
	{
		success = add_char_to_buffer(fsm->result_buf, &fsm->result_buf_size, 
								&fsm->result_buf_count, '$');
		if (!success)
			return (-1);
		return (1);
	}
	return (0);
}

int		fetch_env_var(t_expand *fsm)
{
	char	*value;
	int		success;
	int		i;

	value = ft_getenv(fsm->search_buf, g_env);
	if (!value)
		return (0);
	i = 0;
	while (value[i])
	{
		success = add_char_to_buffer(fsm->result_buf, &fsm->result_buf_size, 
								&fsm->result_buf_count, value[i]);	
		if (!success)
			return (0);
		i++;
	}
	return (1);
}
