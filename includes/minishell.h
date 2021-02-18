/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:13:58 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/18 15:40:25 by darbib           ###   ########.fr       */
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
# include "expand_quote_removal.h"
# include "obj_destructor.h"
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <signal.h>

typedef struct	s_reader {
	t_lexer		lexer;
	t_llparser	parser;
}				t_reader;

t_reader	g_reader;

/*
** g_all_childs is a list of int
*/

t_list			*g_all_childs;

/*
** g_env is a t_list of t_assignment
*/

t_list			*g_env;

int				g_last_command_result;

/*
** g_open_fds is a t_list of ints
*/

t_list			*g_open_fds;

/*
** minishell.c
*/

void			free_all(void);
void			free_tab(char **tab);

/*
** evaluation.c
*/

void			wait_all_childs(void);
void			eval_list(t_shell_list *list);

/*
** execution.c
*/

void			launch(t_simple_command *simple_command, int next_in_pipeline,
					int pipe_stdin, int p[]);
void			redirect_and_launch(t_pipeline *pipeline, int pipe_stdin,
				int p[]);
void			use_redirections(t_simple_command *simple_command);

/*
** built_ins.c
*/

int				is_built_in(t_simple_command *simple_command);
int				launch_built_in(t_simple_command *simple_command);

/*
** parser_interface.c
*/

int				lex_parse(t_reader *reader, char *line);
void			initialize_parser(t_reader *reader);

/*
** free.c
*/

void			free_all(void);

/*
** signals.c
*/

void			signal_handler(int signal);

#endif
