/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:23:42 by darbib            #+#    #+#             */
/*   Updated: 2021/02/10 15:28:08 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_quote_removal.h"
#include "libft.h"

static void	init_transitions_expansion(char transitions[STATE_NB][INPUT_NB])
{
	unsigned char c;

	c = '0';
	while (c <= '9')
		transitions[expand_core_state][c++] = expand_core_state;	
	c = 'A';
	while (c <= 'Z')
	{
		transitions[expand_first_state][c] = expand_core_state;	
		transitions[expand_core_state][c] = expand_core_state;
		c++;
	}
	c = 'a';
	while (c <= 'z')
	{
		transitions[expand_first_state][c] = expand_core_state;	
		transitions[expand_core_state][c] = expand_core_state;	
		c++;
	}
	transitions[expand_first_state]['_'] = expand_core_state;
	transitions[expand_core_state]['_'] = expand_core_state;
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
	transitions[dquote_state]['\\'] = equote_in_dquote_state;
	transitions[dquote_state]['$'] = expand_first_state;
	ft_memset(transitions[equote_state], base_state, INPUT_NB);
	ft_memset(transitions[expand_first_state], base_state, INPUT_NB);
	ft_memset(transitions[expand_core_state], base_state, INPUT_NB);
	ft_memset(transitions[equote_in_dquote_state], dquote_state, INPUT_NB);
	init_transitions_expansion(transitions);
}

void	init_actions(int (*actions[STATE_NB][INPUT_NB])(t_expand*))
{
	ft_bzero(actions, STATE_NB * INPUT_NB * sizeof(void*));
}

#include <stdio.h>
int	expand(char **word)
{
	//int		(*actions[STATE_NB][INPUT_NB])(t_expand*);
	char	transitions[STATE_NB][INPUT_NB];
	const char	*s;
	int		i;
	char	state;

	s = *word;
	init_transitions(transitions);
	//init_actions(actions);
	state = base_state;
	printf("state : %d\n", state);
	i = 0;
	while (s[i])
	{
		printf("--%c--\n", s[i]);
		state = transitions[(int)state][(int)s[i]];
		printf("state : %d\n", state);
		i++;
	}
	return (1);
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
