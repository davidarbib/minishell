/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:45:46 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/18 15:43:46 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	char **tab_mem;

	tab_mem = tab;
	while (*tab)
	{
		free(*tab);
		tab++;
	}
	free(tab_mem);
}

static void	free_assignment(void *content)
{
	free(((t_assignment*)content)->key);
	free(((t_assignment*)content)->value);
	free(content);
}

void	free_all(char *line, char *file, char **tab)
{
	if (tab)
		free(tab);
	if (line)
		free(line);
	if (file)
		free(file);
	if (g_reader.parser.shell_list)
		destroy_shell_list(&g_reader.parser.shell_list);
	ft_lstclear(&g_env, free_assignment);
	ft_lstclear(&g_open_fds, free);
}
