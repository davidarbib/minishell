/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:06:30 by darbib            #+#    #+#             */
/*   Updated: 2021/02/13 00:05:58 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_quote_removal.h"
#include <stdio.h>

int		copy_to_search_buffer(t_expand *fsm)
{
	printf("copy_to_search_buffer\n");
	int success;
	
	success = add_char_to_buffer(fsm->search_buf, &fsm->search_buf_size, 
								&fsm->search_buf_count, fsm->current_char);	
	if (!success)
		return (0);
	return (1);
}

int		copy_to_result_buffer(t_expand *fsm)
{
	printf("copy_to_result_buffer\n");
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

	printf("check_do_escaping\n");
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

int		fetch_and_copy_char_in_search_buffer(t_expand *fsm)
{
	printf("fetch_and_copy_char_in_search_buffer\n");
	if (!fetch_env_var(fsm))
		return (0);
	if (!copy_to_search_buffer(fsm))
		return (0);
	return (1);
}

int		copy_char_in_search_buffer_and_fetch(t_expand *fsm)
{
	printf("copy_char_in_search_buffer_and_fetch\n");
	if (!copy_to_search_buffer(fsm))
		return (0);
	if (!fetch_env_var(fsm))
		return (0);
	return (1);
}

int	fetch_special_var(t_expand *fsm)
{
	printf("fetch_special_var\n");
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
	success = add_char_to_buffer(fsm->result_buf, &fsm->result_buf_size, 
			&fsm->result_buf_count, '$');
	success = add_char_to_buffer(fsm->result_buf, &fsm->result_buf_size, 
			&fsm->result_buf_count, fsm->search_buf[0]);
	if (!success)
		return (-1);
	return (1);
}

int		fetch_env_var(t_expand *fsm)
{
	printf("fetch_env_var\n");
	char	*value;
	int		success;
	int		i;

	value = ft_getenv(fsm->search_buf, g_env);
	printf("search buf : %s\n", fsm->search_buf);
	printf("value : %s\n", value);
	if (value)
	{
		i = 0;
		while (value[i])
		{
			success = add_char_to_buffer(fsm->result_buf, &fsm->result_buf_size, 
					&fsm->result_buf_count, value[i]);	
			if (!success)
				return (0);
			i++;
		}
	}
	ft_bzero(fsm->search_buf, DEFAULT_BUFSIZE);
	fsm->search_buf_count = 0;
	return (1);
}
