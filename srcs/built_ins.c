/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:18:14 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/19 11:24:34 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_built_in	g_built_in[BUILT_IN_NUMBER] = {
	{
		.name = "cd",
		.handler = ft_cd
	},
	{
		.name = "echo",
		.handler = ft_echo
	},
	{
		.name = "env",
		.handler = ft_env
	},
	{
		.name = "unset",
		.handler = ft_unset
	},
	{
		.name = "exit",
		.handler = ft_exit
	},
	{
		.name = "pwd",
		.handler = ft_pwd
	},
	{
		.name = "export",
		.handler = ft_export
	}
};

int			is_built_in(t_simple_command *simple_command)
{
	char	*command;
	int		i;

	if (!simple_command->args)
		return (0);
	command = simple_command->args->content;
	i = 0;
	while (i < BUILT_IN_NUMBER)
	{
		if (ft_strcmp(command, g_built_in[i].name) == 0)
			return (1);
		i++;
	}
	return (0);
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
	tab = (char**)ft_lsttotab(simple_command->args, 8, &size);
	tab[size] = 0;
	ac = 0;
	while (tab[ac])
		ac++;
	ret = run_built_in(tab, ac);
	free(tab);
	return (ret);
}

void		prelaunch_built_in(t_simple_command *simple_command)
{
	int	old_in;
	int	old_out;

	old_in = dup(0);
	old_out = dup(1);
	use_redirections();
	g_last_command_result = launch_built_in(simple_command);
	dup2(old_in, 0);
	close(old_in);
	dup2(old_out, 1);
	close(old_out);
}
