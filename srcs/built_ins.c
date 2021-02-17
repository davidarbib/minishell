/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:18:14 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/17 10:46:46 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_built_in(t_simple_command *simple_command)
{
	int		ret;
	char	*command;

	if (!simple_command->args)
		return (0);
	command = simple_command->args->content;
	ret = 0;
	if (ft_strcmp(command, "cd") == 0 || ft_strcmp(command, "echo") == 0
		|| ft_strcmp(command, "pwd") == 0 || ft_strcmp(command, "exit") == 0
		|| ft_strcmp(command, "env") == 0 || ft_strcmp(command, "unset") == 0)
		ret = 1;
	return (ret);
}

static int	run_built_in(char **tab, int ac)
{
	int i;

	i = 0;
	while (i < BUILT_IN_NUMBER)
	{
		if (ft_strcmp(tab[0], g_built_in[i].name) == 0)
			return (g_built_in[i].handler(ac, tab, &g_env));
		i++;
	}
	return (0);
}

int			launch_built_in(t_simple_command *simple_command)
{
	int					ac;
	char				**tab;
	int					size;
	int					ret;

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
	ret = run_built_in(tab, ac);
	free(tab);
	return (ret);
}
