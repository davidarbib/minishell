/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:52:01 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/17 14:11:36 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		run_once(t_reader *reader, char *line)
{
	parse(reader, line);
	eval_list(reader->parser.shell_list);
}

void		process_env(char **env)
{
	t_assignment	*assignment;
	char			*key;
	char			*value;
	int				i;
	int				j;

	while (*env)
	{
		assignment = malloc(sizeof(t_assignment));
		i = 0;
		while ((*env)[i] != '=')
			i++;
		key = malloc(i + 1);
		ft_strlcpy(key, *env, i + 1);
		assignment->key = key;
		i++;
		j = 0;
		while ((*env)[i + j])
			j++;
		value = malloc(j + 1);
		ft_strlcpy(value, *env + i, j + 1);
		assignment->value = value;
		ft_lstadd_front_elem(&g_env, assignment);
		env++;
	}
}

void		main_loop(void)
{
	char			*line;
	int				result;
	t_reader		reader;

	write(2, FONT_BOLDBLUE "minishell-1.0$ " FONT_RESET, 26);
	result = get_next_line(0, &line);
	if (result == -1)
		printf("minishell: error in get_next_line\n");
	else if (result == 0)
	{
		write(2, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	parse(&reader, line);
	eval_list(reader.parser.shell_list);
	free_all();
}

int			main(int argc, char **argv, char **env)
{
	t_reader		reader;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	process_env(env);
	if (argc == 1)
		while (1)
			main_loop();
	else
	{
		run_once(&reader, argv[1]);
		wait_all_childs();
		free_all();
	}
	return (0);
}
