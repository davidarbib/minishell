/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:18:14 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/16 20:16:56 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	maybe_run_built_in(char **tab, int *ret, int ac)
{
	int i;

	i = 0;
	while (i < BUILT_IN_NUMBER)
	{
		if (ft_strcmp(tab[0], g_built_in[i].name) == 0)
			return (g_built_in[i].handler(ac, tab, &g_env));
		i++;
	}
}

int			launch_built_in(t_simple_command *simple_command)
{
	int					ac;
	char				**tab;
	int					size;
	int					ret;
	int					i;

	ret = 1;
	if (!expand_arguments(simple_command->args))
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	tab = (char**)ft_lsttotab(simple_command->args, 8, &size);
	tab[size] = 0;
	ac = 0;
	while (tab[ac])
		ac++;

	i = 0;
	while (i < BUILT_IN_NUMBER)
	{
		if (ft_strcmp(tab[0], g_built_in[i].name) == 0)
			ret = g_built_in[i].handler(ac, tab, &g_env);
		i++;
	}
	free(tab);
	return (ret);
}
