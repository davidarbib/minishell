/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:23:42 by darbib            #+#    #+#             */
/*   Updated: 2021/02/20 22:11:43 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_quote_removal.h"
#include "parser.h"
#include <stdio.h>

static int		handle_char(char transitions[STATE_NB][INPUT_NB],
						int (*actions[STATE_NB][STATE_NB])(t_expand*),
						t_expand *fsm, char current_char)
{
	int			(*action)(t_expand*);
	int			success;

	fsm->current_char = current_char;
	fsm->next_state = transitions[(int)fsm->state][(int)current_char];
	action = actions[(int)fsm->state][(int)fsm->next_state];
	success = 1;
	if (action)
		success = action(fsm);
	if (!success)
		return (0);
	fsm->state = fsm->next_state;
	return (1);
}

static int		expand_last(t_expand *fsm)
{
	int	success;

	success = 1;
	if (fsm->state == 4)
		success = fetch_special_var(fsm);
	if (fsm->search_buf_count)
		success = fetch_env_var(fsm);
	return (success);
}

static int		expand(char **word, t_expand *fsm,
				char transitions[STATE_NB][INPUT_NB],
				int (*actions[STATE_NB][STATE_NB])(t_expand*))
{
	int			i;

	i = 0;
	while ((*word)[i])
	{
		if (handle_char(transitions, actions, fsm, (*word)[i++]) != 1)
			return (0);
	}
	if (!expand_last(fsm))
		return (0);
	ft_memdel((void**)word);
	*word = ft_strdup(fsm->result_buf);
	if (!*word)
		return (0);
	return (1);
}

int				expand_and_free(char **word,
								char transitions[STATE_NB][INPUT_NB],
								int (*actions[STATE_NB][STATE_NB])(t_expand*))
{
	t_expand	fsm;
	int			success;

	init_expansion(&fsm);
	success = expand(word, &fsm, transitions, actions);
	ft_memdel((void**)&fsm.search_buf);
	ft_memdel((void**)&fsm.result_buf);
	return (success);
}

int				expand_args_redirections(t_list *args, t_list *redirections)
{
	int		(*actions[STATE_NB][STATE_NB])(t_expand*);
	char	transitions[STATE_NB][INPUT_NB];
	t_list	*arg;
	t_list	*redirection_node;
	char	**filename_p;

	init_transitions(transitions);
	init_actions(actions);
	arg = args;
	while (arg)
	{
		if (!expand_and_free((char **)&arg->content, transitions, actions))
			return (0);
		arg = arg->next;
	}
	redirection_node = redirections;
	while (redirection_node)
	{
		filename_p = &((t_io_redirect *)redirection_node->content)->filename;
		if (!expand_and_free(filename_p, transitions, actions))
			return (0);
		redirection_node = redirection_node->next;
	}
	return (1);
}
