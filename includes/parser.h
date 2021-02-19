/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:38:59 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 15:15:04 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "libft.h"
# include "assignment.h"

# define CMD_PREFIX_TYPE		1
# define CMD_NAME_TYPE			2
# define CMD_WORD_TYPE			4
# define CMD_SUFFIX_TYPE		8
# define ASSIGN_TYPE			16
# define WORD_TYPE				32
# define REDIRECT_TYPE			64

enum			e_parser_state
{
	base,
	found,
	multiline,
	no_filename_error,
	sys_error
};

enum			e_redirect_type
{
	i_redirect,
	oc_redirect,
	oa_redirect
};

typedef t_dlist				t_pipeline;
typedef t_list				t_shell_list;

typedef struct				s_simple_command
{
	t_list					*redirections;
	t_list					*assignments;
	t_list					*args;
}							t_simple_command;

typedef struct				s_llparser
{
	t_token					*tokens;
	int						token_idx;
	int						state;
	t_list					*redirections;
	t_list					*assignments;
	t_list					*args;
	t_simple_command		*current_command;
	t_pipeline				*current_pipeline;
	t_shell_list			*shell_list;
}							t_llparser;

typedef struct				s_io_redirect
{
	int						io_number;
	char					*filename;
	enum e_redirect_type	type;
}							t_io_redirect;

int							isredirection_op(t_token *token);
void						detect_ionumber(t_lexer *lexer);
int							parse_prefix(t_llparser *parser);
int							parse_io_redirect(t_llparser *parser);
int							parse_assignment(t_llparser *parser);
void						detect_assignment(t_token *token);
void						detect_assignments(t_lexer *lexer);
t_token						read_token(t_llparser *parser);
t_token						*ref_token(t_llparser *parser);
void						eat(t_llparser *parser);
char						*extract_word(t_token token);
int							parse_word(t_llparser *parser);
int							parse_suffix(t_llparser *parser);
int							parse_cmd_name(t_llparser *parser);
int							parse_cmd_word(t_llparser *parser);
enum e_redirect_type		get_redirection_type(t_token token);
int							store_args(t_list **args, char *arg);
int							parse_simple_command(t_llparser *parser,
							t_pipeline **current_pipeline);
int							parse_pipeline(t_llparser *parser,
							t_pipeline **current_pipeline);
int							parse_shell_list(t_llparser *parser,
							t_shell_list **shell_list);
#endif
