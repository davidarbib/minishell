/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:45:46 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/17 10:23:26 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	while (*tab)
	{
		free(*tab);
		tab++;
	}
}

void	free_all(void)
{
	ft_lstclear(&g_open_fds, free);
}
