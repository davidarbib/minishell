/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 22:40:59 by darbib            #+#    #+#             */
/*   Updated: 2021/02/14 22:42:03 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "expand_quote_removal.h"

static void	init_transitions_lower(char transitions[STATE_NB][INPUT_NB])
{
	unsigned char c;

	c = 'a';
	while (c <= 'z')
	{
		transitions[expand_first_state][c] = expand_core_state;
		transitions[expand_core_state][c] = expand_core_state;
		transitions[expand_first_in_dq_state][c] = expand_core_in_dq_state;
		transitions[expand_core_in_dq_state][c] = expand_core_in_dq_state;
		c++;
	}
	transitions[expand_first_state]['_'] = expand_core_state;
	transitions[expand_core_state]['_'] = expand_core_state;
	transitions[expand_first_in_dq_state]['_'] = expand_core_in_dq_state;
	transitions[expand_core_in_dq_state]['_'] = expand_core_in_dq_state;
	transitions[expand_core_state]['$'] = expand_first_state;
	transitions[expand_core_in_dq_state]['$'] = expand_first_in_dq_state;
	transitions[expand_first_state]['\\'] = equote_state;
	transitions[expand_first_in_dq_state]['\\'] = equote_in_dq_state;
	transitions[expand_core_state]['\\'] = equote_state;
	transitions[expand_core_in_dq_state]['\\'] = equote_in_dq_state;
}

static void	init_transitions_digits_upper(char transitions[STATE_NB][INPUT_NB])
{
	unsigned char c;

	c = '0';
	while (c <= '9')
	{
		transitions[expand_core_state][c] = expand_core_state;
		transitions[expand_core_in_dq_state][c] = expand_core_in_dq_state;
		c++;
	}
	c = 'A';
	while (c <= 'Z')
	{
		transitions[expand_first_state][c] = expand_core_state;
		transitions[expand_core_state][c] = expand_core_state;
		transitions[expand_first_in_dq_state][c] = expand_core_in_dq_state;
		transitions[expand_core_in_dq_state][c] = expand_core_in_dq_state;
		c++;
	}
}

void	init_transitions(char transitions[STATE_NB][INPUT_NB])
{
	ft_memset(transitions[base_state], base_state, INPUT_NB);
	transitions[base_state]['\''] = squote_state;
	transitions[base_state]['\"'] = dquote_state;
	transitions[base_state]['\\'] = equote_state;
	transitions[base_state]['$'] = expand_first_state;
	ft_memset(transitions[squote_state], squote_state, INPUT_NB);
	transitions[squote_state]['\''] = base_state;
	ft_memset(transitions[dquote_state], dquote_state, INPUT_NB);
	transitions[dquote_state]['\"'] = base_state;
	transitions[dquote_state]['\\'] = equote_in_dq_state;
	transitions[dquote_state]['$'] = expand_first_in_dq_state;
	ft_memset(transitions[equote_state], base_state, INPUT_NB);
	ft_memset(transitions[expand_first_state], base_state, INPUT_NB);
	ft_memset(transitions[expand_core_state], base_state, INPUT_NB);
	ft_memset(transitions[equote_in_dq_state], dquote_state, INPUT_NB);
	ft_memset(transitions[expand_first_in_dq_state], dquote_state, INPUT_NB);
	ft_memset(transitions[expand_core_in_dq_state], dquote_state, INPUT_NB);
	init_transitions_digits_upper(transitions);
	init_transitions_lower(transitions);
}

static void	init_expand_actions(int (*actions[STATE_NB][STATE_NB])(t_expand*))
{
	actions[expand_first_state][expand_core_state] = copy_to_search_buffer;
	actions[expand_first_state][base_state] = 
		copy_char_in_search_buffer_and_fetch_special;
	actions[expand_first_state][equote_state] = put_dollar_to_result;
	actions[expand_core_state][expand_core_state] = copy_to_search_buffer;
	actions[expand_core_state][expand_first_state] = fetch_env_var;
	actions[expand_core_state][base_state] = fetch_env_var;
	actions[expand_first_in_dq_state][expand_core_in_dq_state] = 
		copy_to_search_buffer;
	actions[expand_first_in_dq_state][dquote_state] =
		copy_char_in_search_buffer_and_fetch_special;
	actions[expand_first_in_dq_state][equote_in_dq_state] = 
		put_dollar_to_result;
	actions[expand_core_in_dq_state][expand_core_in_dq_state] =
		copy_to_search_buffer;
	actions[expand_core_in_dq_state][expand_first_in_dq_state] = fetch_env_var;
	actions[expand_core_in_dq_state][dquote_state] = fetch_env_var;
	actions[expand_core_in_dq_state][equote_state] = fetch_env_var;
}

void	init_actions(int (*actions[STATE_NB][STATE_NB])(t_expand*))
{
	int	i;
	int	j;

	ft_bzero(actions, STATE_NB * STATE_NB * sizeof(void*));
	i = base_state;
	while (i < STATE_NB)
	{
		j = base_state;
		while (j < STATE_NB)
			actions[i][j++] = NULL;
		i++;
	}
	actions[base_state][base_state] = copy_to_result_buffer;
	actions[equote_state][base_state] = copy_to_result_buffer;
	actions[squote_state][squote_state] = copy_to_result_buffer;
	actions[dquote_state][dquote_state] = copy_to_result_buffer;
	actions[equote_in_dq_state][dquote_state] = check_do_escaping;
	init_expand_actions(actions);
}
