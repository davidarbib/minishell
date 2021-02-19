/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:31:46 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/19 14:17:41 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		test_if_numeric(char *str)
{
	int i;

	i = 0;
	if (str[0] != '-' && !('0' <= str[i] && str[i] <= '9'))
		return (0);
	i++;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	free_and_exit(int i)
{
	free_before_exit(NULL, NULL, NULL, NULL);
	exit(i);
}

int		ft_exit(int ac, char **av, t_list **envlist)
{
	(void)envlist;
	ft_dprintf(2, "exit\n");
	if (ac == 1)
		free_and_exit(127);
	if (!(test_if_numeric(av[1])))
	{
		ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
									av[1]);
		free_and_exit(2);
	}
	if (ac > 2)
	{
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		return (1);
	}
	free_and_exit(ft_atoi_strict(av[1]) % 256);
	return (0);
}
