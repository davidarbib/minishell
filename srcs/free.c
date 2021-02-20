/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:45:46 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/20 13:55:50 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_tab(char **tab)
{
	char **tab_mem;

	if (tab)
	{
		tab_mem = tab;
		while (*tab)
		{
			free(*tab);
			tab++;
		}
		free(tab_mem);
	}
}

static void	free_assignment(void *content)
{
	free(((t_assignment*)content)->key);
	free(((t_assignment*)content)->value);
	free(content);
}

void		free_and_continue(char *line, char *file, char **tab, char **env)
{
	free(tab);
	free(line);
	free(file);
	free_tab(env);
}

void		free_before_exit(char *line, char *file, char **tab, char **env)
{
	free(tab);
	free(line);
	free(file);
	free_tab(env);
	if (g_reader.parser.shell_list)
		destroy_shell_list(&g_reader.parser.shell_list);
	ft_lstclear(&g_env, free_assignment);
}

void		close_and_free(void *content)
{
	if (((t_redirection*)content)->in != 0)
		close(((t_redirection*)content)->in);
	if (((t_redirection*)content)->out != 1)
		close(((t_redirection*)content)->out);
	free(content);
}
