/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:13:58 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/12 11:47:09 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "lexer.h"
# include "parser.h"
# include "font_color.h"
# include "environ.h"
# include "built_ins.h"
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <signal.h>

# define BUILT_IN		0
# define NOT_BUILT_IN	1

typedef struct	s_reader {
	t_lexer		lexer;
	t_llparser	parser;
}				t_reader;

/*
** g_all_childs is a list of int
*/

t_list	*g_all_childs;

/*
** g_env is a t_list of t_assignment
*/

t_list	*g_env;

int		g_last_command_result;

/*
** g_open_fds is a t_list of ints
*/

t_list	*g_open_fds;

/*
** execution.c
*/

int		launch_built_in(t_simple_command* simple_command);
void	wait_all_childs(void);
void	launch(t_simple_command *simple_command, int next_in_pipeline, int pipe_stdin, int p[]);

/*
** parser_interface.c
*/

void	parse(t_reader *reader, char *line);
void	initialize_parser(t_reader *reader);

#endif
