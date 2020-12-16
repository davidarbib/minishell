/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:26:10 by darbib            #+#    #+#             */
/*   Updated: 2020/12/17 00:22:37 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"

typedef struct	s_io_file
{
	t_token		*redir_op;
	t_token		*filename;
}				t_io_file;

typedef struct	s_io_redirect
{
	t_token		*io_number;
	t_io_file	*io_file;
}				t_io_redirect;

union			u_redirect_word
{
	t_io_redirect	io_redirect;
	t_token			word;
};

union			u_redirect_assign
{
	t_io_redirect	io_redirect;
	t_token			assignment_word;
};

typedef struct	s_cmd_suffix
{
	struct s_cmd_suffix		*cmd_suffix;
	union u_redirect_word	*redirect_word;
}				t_cmd_suffix;

typedef struct	s_cmd_prefix
{
	struct s_cmd_prefix		*cmd_prefix;
	union u_redirect_word	*redirect_word;
}				t_cmd_prefix;

typedef	t_token	t_cmd_name;
typedef	t_token	t_cmd_word;

union			u_cmd_prefix_name
{
	t_cmd_prefix	cmd_prefix;
	t_cmd_name		cmd_name;
};

union			u_cmd_word_suffix
{
	t_cmd_word		cmd_word;
	t_cmd_suffix	cmd_suffix;
};

typedef struct	s_simple_command
{
	struct s_cmd_prefix		*cmd_prefix;
	union u_cmd_prefix_name	*cmd_prefix_name;
}				t_simple_command;

typedef struct s_complete_command
{
	
}				
#endif
