/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:38:45 by darbib            #+#    #+#             */
/*   Updated: 2021/02/17 21:17:28 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# define TOKENS_NB	6
# define FSMBUFSIZE	1024
# define LEXERSIZE	32

/*
** token types
**
** WORD type means non operator TOKEN in lexer layer
** further distinctions on WORD are made in parser layer :
** the token can be requalified IONUMBER if it is a number
** next to redirection operator (My posix interpretation :) );
** please add operators after pipe, and non-operator before
*/
enum			e_token
{
	DUMMY_TOKEN,
	NEWLINE_TOKEN,
	WORD_TOKEN,
	ASSIGNMENT_TOKEN,
	TEXT_TOKEN,
	IONUMBER_TOKEN,
	PIPE_TOKEN,
	SCOLON_TOKEN,
	DGREAT_TOKEN,
	GREAT_TOKEN,
	LESS_TOKEN
};

enum			e_fsm
{
	NORMAL_STATE,
	QUOTE_STATE,
	DQUOTE_STATE,
	ESCAPE_STATE,
	COMMENT_STATE,
};

enum			e_lexer
{
	OK_STATE,
	MULTILINE_STATE,
	KO_STATE
};

typedef struct	s_token
{
	enum e_token	type;
	char			*value;
	size_t			size;
}				t_token;

/*
typedef struct	s_token
{
	enum e_token		type;
	const unsigned char	*value;
	size_t				size;
}				t_token;
*/

/*
** in lexer and fsm structures 'size' field refers to allocated memory area for 
** tokens or buffer. 
** 'count' refers to token array or chars buffer current_index.
*/
typedef struct	s_lexer
{
	t_token			*tokens;
	int				count;
	size_t			size;
	enum e_lexer	state;
}				t_lexer;

typedef struct	s_fsm
{
	enum e_fsm	state;
	t_token		current_token;
	char		*buf;
	int			count;
	size_t		size;
}				t_fsm;

int			is_operator(t_token *token);
t_token		match_operator(char *tested_op);
int			delimit_token(t_lexer *lexer, t_fsm *fsm);
int			check_operator_completion(t_lexer *lexer, t_fsm *fsm, 
			char current_char);
int			check_quoting_char(t_fsm *fsm, char current_char);
int			check_substitution_mark(t_fsm *fsm, char current_char);
int			check_new_op(t_lexer *lexer, t_fsm *fsm, char current_char);
int			check_blank(t_lexer *lexer, t_fsm *fsm, char current_char);
t_lexer		analyse_command_wrapper(char *command);
t_lexer		analyse_command(char *command, t_lexer *lexer, t_fsm *fsm);
int			init_lexer_fsm(t_lexer *lexer, t_fsm *fsm);
int			add_char_to_fsm_buffer(t_fsm *fsm, char c);
int			add_token(t_lexer *lexer, t_token token);
void		exit_lexing(t_lexer *lexer, t_fsm *fsm);
void		destroy_fsm(t_fsm *fsm);
void		destroy_lexer(t_lexer *lexer);
#endif
