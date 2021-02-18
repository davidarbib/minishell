/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 21:26:25 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/18 22:03:20 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(int ac, char **av, t_list **envlist)
{
	t_list	*tmp;

	(void)ac;
	(void)av;
	(void)envlist;
	tmp = g_env;
	while (tmp)
	{
		ft_printf("%s=%s\n", ((t_assignment*)tmp->content)->key,
				((t_assignment*)tmp->content)->value);
		tmp = tmp->next;
	}
	return (0);
}
