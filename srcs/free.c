/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:45:46 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/19 10:24:41 by fyusuf-a         ###   ########.fr       */
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
	/*if (g_reader.parser.shell_list)
		destroy_shell_list(&g_reader.parser.shell_list);*/
	ft_lstclear(&g_env, free_assignment);
	/*ft_lstclear(&g_redirections, free);*/
	/*ft_lstclear(&g_open_fds, free);*/
}

void	close_and_free(void *content)
{
	if (((t_redirection*)content)->in != 0)
		close(((t_redirection*)content)->in);
	if (((t_redirection*)content)->out != 1)
		close(((t_redirection*)content)->out);
	free(content);
}
