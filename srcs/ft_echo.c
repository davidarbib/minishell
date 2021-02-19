/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:06:40 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/18 22:01:12 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(int ac, char **av, t_list **env_list)
{
	int	newline;
	int i;

	(void)env_list;
	i = 1;
	newline = 1;
	if (ac > 1 && ft_strcmp("-n", av[1]) == 0)
	{
		newline = 0;
		i++;
	}
	while (i < ac)
	{
		ft_printf("%s", av[i]);
		if (i != ac - 1)
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}
