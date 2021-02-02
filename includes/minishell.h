/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:13:58 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/02 13:36:38 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "lexer.h"
# include "parser.h"
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct	s_reader {
	t_lexer		lexer;
	t_llparser	parser;
}				t_reader;

typedef struct	s_process {
	int	pid;
	int	pipe_out;
}				t_process;

/*
** g_all_childs is a list of t_process
*/

t_list	*g_all_childs;

/*
** g_env is a t_list of t_assignment
*/

t_list	*g_env;

t_list	*lookup(char *key, t_list *assignments);

/*
** execution.c
*/

void	wait_all_childs(void);
void	redirect_and_launch(t_pipeline *pipeline, int pipe_stdin, int p[]);

/*
** parser_interface.c
*/

int		parse(t_reader *reader, char *line);
void	initialize_parser(t_reader *reader);

#endif
