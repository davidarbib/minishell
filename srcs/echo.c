/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:06:40 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/02 14:24:42 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo(int argc, char** argv, char **env)
{
	(void)env;
	int	newline;
	int i;

	i = 1;
	newline = 1;
	if (argc > 1 && ft_strcmp("-n", argv[1]) == 0)
	{
		newline = 0;
		i++;
	}
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i != argc - 1)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
