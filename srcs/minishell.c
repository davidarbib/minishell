/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:52:01 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/20 22:13:16 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void		process_env(char **env)
{
	int		shlvl;
	t_list	*tmp;

	g_env = to_environ_list(env);
	tmp = g_env;
	while (tmp)
	{
		if (ft_strcmp(((t_assignment*)tmp->content)->key, "SHLVL") == 0)
		{
			shlvl = ft_atoi(((t_assignment*)tmp->content)->value);
			free(((t_assignment*)tmp->content)->value);
			((t_assignment*)tmp->content)->value = ft_itoa(shlvl + 1);
			break ;
		}
		tmp = tmp->next;
	}
}

void		main_loop(void)
{
	char			*line;
	int				result;

	write(2, "minishell-1.0$ ", 15);
	result = get_next_line(0, &line);
	if (result == -1)
		printf("minishell: error in get_next_line\n");
	else if (result == 0)
	{
		write(2, "exit\n", 5);
		free_before_exit(line);
		exit(EXIT_SUCCESS);
	}
	result = lex_parse(&g_reader, line);
	if (result == -1)
	{
		free_before_exit(line);
		exit(EXIT_FAILURE);
	}
	if (result == 0)
		eval_list(g_reader.parser.shell_list);
	destroy_shell_list(&g_reader.parser.shell_list);
}

int			main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	process_env(env);
	while (1)
		main_loop();
	return (0);
}
