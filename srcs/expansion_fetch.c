/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_fetch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 23:37:51 by darbib            #+#    #+#             */
/*   Updated: 2021/02/14 23:42:39 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_quote_removal.h"
#include "minishell.h"

static int	fetch_exit_status(t_expand *fsm)
{
	char	*exit_s;

	if (fsm->search_buf[0] == '?')
	{
		exit_s = ft_itoa(g_last_command_result);
		if (!exit_s)
			return (-1);
		ft_memmove(fsm->result_buf + fsm->result_buf_count, exit_s,
					ft_strlen(exit_s));
		return (1);
	}
	return (0);
}

int	fetch_special_var(t_expand *fsm)
{
	//printf("fetch_special_var\n");
	int		success;

	if (fsm->search_buf_count == 0)
	{
		success = add_char_to_buffer(fsm->result_buf, &fsm->result_buf_size, 
								&fsm->result_buf_count, '$');
		if (!success)
			return (-1);
		return (1);
	}
	success = fetch_exit_status(fsm);
	if (success == 1)
		return (1);
	if (success == -1)
		return (-1);
	success = add_char_to_buffer(fsm->result_buf, &fsm->result_buf_size, 
			&fsm->result_buf_count, '$');
	success = add_char_to_buffer(fsm->result_buf, &fsm->result_buf_size, 
			&fsm->result_buf_count, fsm->search_buf[0]);
	if (!success)
		return (-1);
	return (1);
}

static int		handle_quote_after_dollar(t_expand *fsm)
{
	//printf("handle_quote_after_dollar\n");
	int success;

	success = 1;
	if (fsm->current_char == '\'' && fsm->state == expand_first_state)
		fsm->next_state = squote_state;
	if (fsm->current_char == '"' && fsm->state == expand_first_state)
		fsm->next_state = dquote_state; 
	if (fsm->current_char == '"' && fsm->state == expand_first_in_dq_state)
	{
		success = add_char_to_buffer(fsm->result_buf, &fsm->result_buf_size, 
								&fsm->result_buf_count, '$');
		fsm->next_state = base_state;
	}
	if (!success)
		return (-1);
	return (1);
}

int		copy_char_in_search_buffer_and_fetch_special(t_expand *fsm)
{
	int	success;

	if (fsm->current_char == '"' || fsm->current_char == '\'')
	{
		handle_quote_after_dollar(fsm);
		return (1);
	}
	//printf("copy_char_in_search_buffer_and_fetch_special\n");
	if (!copy_to_search_buffer(fsm))
		return (-1);
	success = fetch_special_var(fsm);
	ft_bzero(fsm->search_buf, fsm->search_buf_size);
	fsm->search_buf_count = 0;
	return (success);
}

int		fetch_env_var(t_expand *fsm)
{
	//printf("fetch_env_var\n");
	char	*value;
	int		success;
	int		i;

	value = ft_getenv(fsm->search_buf, g_env);
	//printf("search buf : %s\n", fsm->search_buf);
	//printf("value : %s\n", value);
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
	ft_bzero(fsm->search_buf, fsm->search_buf_size);
	fsm->search_buf_count = 0;
	return (1);
}
