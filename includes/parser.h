/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:26:10 by darbib            #+#    #+#             */
/*   Updated: 2021/01/27 17:56:16 by darbib           ###   ########.fr       */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "libft.h"
# include "assignment.h"

# define cmd_prefix_type		1
# define cmd_name_type			2
# define cmd_word_type			4
# define cmd_suffix_type		8
# define assign_type			16	
# define word_type				32
# define redirect_type			64

//----Structures a la sortie du parser---
// fait pas attention a t_llparser actuel plus pratique pour mes tests unitaires
//typedef struct	s_llparser
//{
//	t_token				*tokens;
//	int					token_idx;
//	int					state;
//	t_shell_list		*shell_list;
//}				t_llparser;
//
//typedef t_list t_shell_list;
//typedef t_dlist t_pipeline;
//
// une t_shell_list a pour content une *t_pipeline
// une t_pipeline a pour content une *t_simple_command
//
// attention : t_pipeline est doublement chainee dans l'idee
//
// toutes les infos sont recuperees des tokens lors du parsing,
// pour free les tokens au plus vite
// on gardera juste la shell_list
//
// je me tate a executer les assignations pdt le parsing mais jaime bien les archis
// en couches, quen penses tu ?
//-----------------------------------------------------------------------------

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

typedef t_dlist	t_pipeline;
typedef t_list	t_shell_list;

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
	t_simple_command	*current_command;
	t_pipeline			*current_pipeline;
	t_shell_list		*shell_list;
}				t_llparser;


typedef struct	s_io_redirect
{
	int						io_number;
	char					*filename;
	enum e_redirect_type	type;
}				t_io_redirect;


int						isredirection_op(t_token *token);
void					detect_ionumber(t_lexer *lexer);
int						parse_prefix(t_llparser *parser);
int						parse_io_redirect(t_llparser *parser);
int						parse_assignment(t_llparser *parser);
void					detect_assignment(t_token *token);
void					detect_assignments(t_lexer *lexer);
t_token					read_token(t_llparser *parser);
t_token					*ref_token(t_llparser *parser);
void					eat(t_llparser *parser);
char					*extract_word(t_token token);
int						parse_word(t_llparser *parser);
int						parse_suffix(t_llparser *parser);
int						parse_cmd_name(t_llparser *parser);
int						parse_cmd_word(t_llparser *parser);
enum e_redirect_type	get_redirection_type(t_token token);
int						store_args(t_list **args, char *arg);
int						parse_simple_command(t_llparser *parser, 
						t_pipeline **current_pipeline);
int						parse_pipeline(t_llparser *parser, 
						t_pipeline **current_pipeline);
int						parse_shell_list(t_llparser *parser, 
						t_shell_list **shell_list);
#endif
