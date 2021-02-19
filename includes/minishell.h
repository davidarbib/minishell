/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:13:58 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/19 14:28:28 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
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

t_reader		g_reader;

/*
** g_all_childs is a list of int
*/

t_list			*g_all_childs;

/*
** g_env is a t_list of t_assignment
*/

t_list			*g_env;

int				g_last_command_result;

typedef struct	s_redirection {
	int	in;
	int	out;
}				t_redirection;

/*
** g_redirections is a t_list of t_redirections
*/

t_list			*g_redirections;
t_list			*g_temp_redirections;

/*
** evaluation.c
*/

void			wait_all_childs(void);
void			eval_list(t_shell_list *list);

/*
** execution.c
*/

typedef struct 	s_pipe {
	int			is_next_in_pipeline;
	int			pipe_stdin;
	int			p[2];
}				t_pipe;

void			prelaunch_built_in(t_simple_command *simple_command);
void			launch(t_simple_command *simple_command, t_pipe pipe);
//void			launch(t_simple_command *simple_command, int next_in_pipeline,
					//int pipe_stdin, int p[]);
//void			redirect_and_launch(t_pipeline *pipeline, t_pipe pipe);
//void			redirect_and_launch(t_pipeline *pipeline, int pipe_stdin,
				//int p[]);

/*
** execution2.c
*/

//void			use_pipes(int next_in_pipeline, int pipe_stdin, int p[]);
void			use_pipes(t_pipe pipe);
void			set_redirections(t_pipeline	*pipeline);
void			use_redirections(void);

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

void			free_tab(char **tab);
void			free_and_continue(char *line, char *file, char **tab, char **env);
void			free_before_exit(char *line, char *file, char **tab, char **env);
void			close_and_free(void *content);

/*
** signals.c
*/

void			signal_handler(int signal);

#endif
