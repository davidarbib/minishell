/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:32:10 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/16 10:53:06 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmp(void *content, void *data_ref)
{
	if (ft_strcmp(((t_assignment*)content)->key, data_ref) == 0)
		return (0);
	return (1);
}

void		free_fct(void *ptr)
{
	(void)ptr;
}

int			ft_unset(int ac, char **av, t_list **envlist)
{
	int i;

	(void)envlist;
	i = 1;
	while (i < ac)
	{
		ft_lstremove_if(&g_env, av[i], cmp, free_fct);
		i++;
	}
	return (0);
}
