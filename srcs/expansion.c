/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:23:42 by darbib            #+#    #+#             */
/*   Updated: 2021/02/12 15:29:35 by darbib           ###   ########.fr       */
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
	transitions[expand_first_in_dq_state][c] = expand_core_in_dq_state;
	transitions[expand_core_in_dq_state][c] = expand_core_in_dq_state;
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
	actions[expand_first_in_dq_state][expand_core_in_dq_state] = 
		copy_to_search_buffer;
	actions[expand_first_in_dq_state][dquote_state] = fetch_special_var;
	actions[expand_core_in_dq_state][expand_core_in_dq_state] =
		copy_to_search_buffer;
	actions[base_state][base_state] = copy_to_result_buffer;
	actions[base_state][base_state] = copy_to_result_buffer;
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
	actions[dquote_state][expand_first_in_dq_state] = copy_to_search_buffer;
	actions[equote_in_dq_state][dquote_state] = check_do_escaping;
}

int		add_char_to_buffer(char *buf, size_t *size, size_t *count, char c)
{
	if ((size_t)(*count) + 1 == *size)
	{
		buf = (char *)ft_realloc(buf, *size, *size * 2);
		if (!buf)
			return (0);
		*size *= 2;
	}
	buf[*count] = c;
	(*count)++;
	return (1);
}

int		init_expansion(t_expand *fsm) 
{
	fsm->state = base_state;
	fsm->search_buf_size = DEFAULT_BUFSIZE;
	fsm->result_buf_size = DEFAULT_BUFSIZE;
	fsm->search_buf = NULL;
	fsm->result_buf = NULL;
	fsm->search_buf = (char *)ft_calloc(fsm->search_buf_size, sizeof(char));
	fsm->result_buf = (char *)ft_calloc(fsm->result_buf_size, sizeof(char));
	fsm->search_buf_count = 0;
	fsm->result_buf_count = 0;
	if (fsm->search_buf && fsm->result_buf)
		return (1);
	return (0);
}

#include <stdio.h>
static int	handle_char(char transitions[STATE_NB][INPUT_NB], 
						int (*actions[STATE_NB][STATE_NB])(t_expand*), 
						t_expand *fsm, char current_char)
{
	int			next_state;
	int			(*action)(t_expand*);
	int			success;

	printf("--%c--\n", current_char);
	next_state = transitions[(int)fsm->state][(int)current_char];
	action = actions[(int)fsm->state][(int)next_state];
	if (action)
		success = action(fsm);
	if (!success)
		return (0);
	fsm->state = next_state;
	printf("state : %d\n", fsm->state);
}

int		expand(char **word)
{
	int			(*actions[STATE_NB][STATE_NB])(t_expand*);
	char		transitions[STATE_NB][INPUT_NB];
	int			i;
	t_expand	fsm;

	init_expansion(&fsm);
	init_transitions(transitions);
	init_actions(actions);
	printf("state : %d\n", fsm.state);
	i = 0;
	while ((*word)[i])
	{
		if (handle_char(transitions, actions, &fsm, (*word)[i++]) != 1)
			return (0);
	}
	ft_memdel((void**)word);
	*word = ft_strdup(fsm.result_buf);
	if (!word)
		return (0);
	return (1);
	//free
}

#include <string.h>
int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	//char *word = strdup("$HOME");
	//char *word = strdup("e$HOME");
	//char *word = strdup("$0HOME");
	//char *word = strdup("$9HOME");
	//char *word = strdup("$$HOME");
	//char *word = strdup("$");
	//char *word = strdup("ez$");
	//char *word = strdup("$$");
	//char *word = strdup("$_HOME");
	//char *word = strdup("_$HOME");
	//char *word = strdup("$H0ME__OK");
	//char *word = strdup("\'$H0ME\'__OK");
	//char *word = strdup("\"$H0ME\"__OK");
	//char *word = strdup("\\$H0ME__OK");
	//char *word = strdup("\"\\$H0ME\"__OK");
	char *word = strdup("\"$H0M\\E\"__OK");
	expand(&word);
	printf("cc\n");
	return (0);
}
