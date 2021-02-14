/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:23:42 by darbib            #+#    #+#             */
/*   Updated: 2021/02/14 22:56:48 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_quote_removal.h"
#include <stdio.h>

static int	handle_char(char transitions[STATE_NB][INPUT_NB], 
						int (*actions[STATE_NB][STATE_NB])(t_expand*), 
						t_expand *fsm, char current_char)
{
	int			(*action)(t_expand*);
	int			success;

	//printf("--%c--\n", current_char);
	fsm->current_char = current_char;
	fsm->next_state = transitions[(int)fsm->state][(int)current_char];
	action = actions[(int)fsm->state][(int)fsm->next_state];
	success = 1;
	if (action)
		success = action(fsm);
	if (!success)
		return (0);
	fsm->state = fsm->next_state;
	//printf("state : %d\n", fsm->state);
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

	//printf("state : %d\n", fsm->state);
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

int		expand_and_free(char **word, char transitions[STATE_NB][INPUT_NB], 
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

int		expand_arguments(t_list	*args)
{
	int		(*actions[STATE_NB][STATE_NB])(t_expand*);
	char	transitions[STATE_NB][INPUT_NB];
	t_list	*arg;

	init_transitions(transitions);
	init_actions(actions);
	arg = args;
	while (arg)
	{
		if (expand_and_free((char **)&arg->content, transitions, actions))
			return (0);
		arg = arg->next;
	}
	return (1);
}

#include <string.h>
#include "obj_destructor.h"
/*
int main(int ac, char **av, char **envp)
{
	g_env = to_environ_list(envp);
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
	//char *word = strdup("\'$HOME\'__OK");
	//char *word = strdup("\"$HOME\"__OK");
	//char *word = strdup("\\$HOME__OK");
	//char *word = strdup("\\$HOME");
	//char *word = strdup("\"\\$HOME\"__OK");
	//char *word = strdup("\"$HOM\\E\"__OK");
	//char *word = strdup("$?");
	//char *word = strdup("$+");
	//char *word = strdup("$HOME$PWD");
	//char *word = strdup("$+HOME");
	//char *word = strdup("$+$PWD");
	//char *word = strdup("$$PWD");
	//char *word = strdup("\"$?\"");
	//char *word = strdup("\"$+\"");
	//char *word = strdup("\"$HOME$PWD\"");
	//char *word = strdup("\"$+HOME\"");
	//char *word = strdup("\"$+$PWD\"");
	//char *word = strdup("\"$$PWD\"");
	//char *word = strdup("$\\HOME$PWD");
	//char *word = strdup("$\"HOME\"$PWD");
	//char *word = strdup("$\"HOME$\"PWD");
	//char *word = strdup("$\"o\"");
	//char *word = strdup("$\'o\'");
	//char *word = strdup("$\\o");
	//char *word = strdup("$\"\\HOME$\"PWD");
	//char *word = strdup("$\"\\HOME\"$PWD");
	//char *word = strdup("\'$+\'");
	//char *word = strdup("\"$\\+\"");
	//char *word = strdup("\'$\\+\'");
	//char *word = strdup("\'$\\+\'");
	//char *word = strdup("\\$\\+\\");
	//char *word = strdup("\"\\$\\+\\\"\"");
	expand_and_free(&word);
	printf("%s\n", word);
	ft_memdel((void**)&word);
	ft_lstclear(&g_env, del_assign_content);
	return (0);
}
*/
