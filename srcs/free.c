/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:45:46 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/17 14:35:26 by fyusuf-a         ###   ########.fr       */
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

static void	free_assignment(void *content)
{
	free(((t_assignment*)content)->key);
	free(((t_assignment*)content)->value);
	free(content);

}

void	free_all(void)
{
	ft_lstclear(&g_env, free_assignment);
	ft_lstclear(&g_open_fds, free);
}
