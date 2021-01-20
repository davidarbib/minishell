/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:26:10 by darbib            #+#    #+#             */
/*   Updated: 2021/01/20 15:24:03 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "libft.h"

# define cmd_prefix_type		1
# define cmd_name_type			2
# define cmd_word_type			4
# define cmd_suffix_type		8
# define assign_type			16	
# define word_type				32
# define redirect_type			64

enum			e_parser_state
{
	base,
	found,
	error
};

enum			e_redirect_type
{
	i_redirect,
	oc_redirect,
	oa_redirect
};

typedef struct	s_simple_command
{
	t_list		*redirections;
	t_list		*assignments;
	t_list		*args;
}				t_simple_command;

typedef struct	s_llparser
{
	t_token				*tokens;
	int					token_idx;
	int					state;
	t_list				*redirections;
	t_list				*assignments;
	t_list				*args;
	t_simple_command	*command;
}				t_llparser;

typedef struct	s_io_redirect
{
	int						io_number;
	char					*filename;
	enum e_redirect_type	type;
}				t_io_redirect;

typedef struct	s_assignment
{
	char					*key;
	char					*value;
}				t_assignment;

typedef struct	s_cmd_suffix
{
	int						type_flag;
	struct s_cmd_suffix		*cmd_suffix;
	union u_redirect_word	*redirect_word;
}				t_cmd_suffix;

typedef struct	s_cmd_prefix
{
	int						type_flag;
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

/*
typedef struct	s_simple_command
{
	int						type_flag;
	union u_cmd_prefix_name	*cmd_prefix_name;
	union u_cmd_word_suffix	*cmd_word_suffix;
	t_cmd_suffix			*cmd_suffix;
}				t_simple_command;
*/

typedef struct	s_pipeline
{
	struct s_pipeline	*pipeline;
	t_token				*pipe_token;
	t_simple_command	*simple_command;
}				t_pipeline;	

typedef struct	s_shell_list
{
	struct s_shell_list	*shell_list;
	t_token				*separator;
	t_pipeline			*pipeline;
}				t_shell_list;

int						isredirection_op(t_token *token);
void					detect_ionumber(t_lexer *lexer);
void					parse_prefix(t_llparser *parser);
void					parse_io_redirect(t_llparser *parser);
void					parse_assignment(t_llparser *parser);
void					detect_assignment(t_token *token);
void					detect_assignments(t_lexer *lexer);
t_token					read_token(t_llparser *parser);
t_token					*ref_token(t_llparser *parser);
void					eat(t_llparser *parser);
char					*extract_word(t_token token);
void					parse_word(t_llparser *parser);
enum e_redirect_type	get_redirection_type(t_token token);
int						store_args(t_list **args, char *arg);
void					parse_simple_command(t_llparser *parser);
#endif
