/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:31:46 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/12 15:59:12 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exit(int ac, char **av, t_list **envlist)
{
	int i = 0;

	while (av[1][i])
		if (!('0' <= av[1][i] && av[1][i] <= '9'))
		{
			dprintf(2, "exit\n"
					"minishell: exit: %s: numeric argument required\n");
			exit(255);
		}


	exit(av[1]);
}
