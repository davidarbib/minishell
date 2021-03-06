/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 11:37:07 by darbib            #+#    #+#             */
/*   Updated: 2021/02/20 22:13:10 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "obj_destructor.h"
#include "expand_quote_removal.h"
#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	int		(*actions[STATE_NB][STATE_NB])(t_expand*);
	char	transitions[STATE_NB][INPUT_NB];

	g_env = to_environ_list(envp);
	(void)ac;
	(void)av;
	//char *word = strdup("$HOME");
	//char *word = strdup("$HOME\\");
	//char *word = strdup("\"$HOME\\\"\"");
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
	//char *word = strdup("\"$USER\\\"\"");
	//char *word = strdup(" \"$PWD $USER \"");
	//char *word = strdup("\"$PWD $USER. \"");
	//char *word = strdup("\"$USER\'. \"");
	char *word = strdup("\"$USER\\\'. \"");
	init_transitions(transitions);
	init_actions(actions);
	expand_and_free(&word, transitions, actions);
	printf("%s\n", word);
	ft_memdel((void**)&word);
	ft_lstclear(&g_env, del_assign_content);
	return (0);
}
