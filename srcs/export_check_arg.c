/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:56:10 by darbib            #+#    #+#             */
/*   Updated: 2021/02/20 13:59:01 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assignment.h"
#include "ft_printf.h"

static int	check_word(char *word,
						unsigned char transitions[A_STATE_NB][A_INPUT_NB])
{
	unsigned char	state;
	int				i;

	i = 0;
	state = BASE_STATE;
	while (word[i])
	{
		state = transitions[state][(unsigned char)word[i]];
		if (state == ERROR_STATE)
			return (0);
		i++;
	}
	if (state == EQUAL_STATE)
		return (1);
	return (0);
}

int			check_export_arg(char *word)
{
	static unsigned char	transitions[A_STATE_NB][A_INPUT_NB];
	static int				filled_table = 0;
	int						success;

	if (!filled_table)
	{
		init_transitions_tb(transitions);
		filled_table = 1;
	}
	success = check_word(word, transitions);
	if (!success)
	{
		ft_dprintf(2, "minishell: export: `%s\': not a valid identifier\n",
					word);
	}
	return (success);
}
