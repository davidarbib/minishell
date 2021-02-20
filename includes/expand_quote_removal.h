/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_removal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:26:18 by darbib            #+#    #+#             */
/*   Updated: 2021/02/20 19:40:11 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_QUOTE_REMOVAL_H
# define EXPAND_QUOTE_REMOVAL_H

# include <stdlib.h>
# include "environ.h"
# include "libft.h"
# include "parser.h"

# define STATE_NB			9
# define INPUT_NB			128
# define DEFAULT_BUFSIZE	4096

typedef enum	e_expand_fsm
{
	base_state,
	squote_state,
	dquote_state,
	equote_state,
	expand_first_state,
	expand_core_state,
	equote_in_dq_state,
	expand_first_in_dq_state,
	expand_core_in_dq_state
}				t_expand_fsm;

typedef struct	s_expand
{
	char		*search_buf;
	char		*result_buf;
	size_t		search_buf_size;
	size_t		result_buf_size;
	size_t		search_buf_count;
	size_t		result_buf_count;
	int			state;
	int			next_state;
	char		current_char;
}				t_expand;

void			init_actions(int (*actions[STATE_NB][STATE_NB])(t_expand*));
void			init_transitions(char transitions[STATE_NB][INPUT_NB]);
int				init_expansion(t_expand *fsm);
int				add_char_to_buffer(char *buf, size_t *size, size_t *count,
				char c);
int				copy_to_search_buffer(t_expand *fsm);
int				copy_to_result_buffer(t_expand *fsm);
int				fetch_env_var(t_expand *fsm);
int				fetch_special_var(t_expand *fsm);
int				check_do_escaping(t_expand *fsm);
int				copy_char_in_search_buffer_and_fetch(t_expand *fsm);
int				copy_char_in_search_buffer_and_fetch_special(t_expand *fsm);
int				put_dollar_to_result(t_expand *fsm);
int				expand_arguments(t_list	*args);
int				expand_and_free(char **word,
				char transitions[STATE_NB][INPUT_NB],
				int (*actions[STATE_NB][STATE_NB])(t_expand*));
int				expand_args_redirections(t_list *args, t_list *redirections);
int				expand_pipeline(t_pipeline *pipeline);
int				fetch_and_copy_char_to_result_buffer(t_expand *fsm);
#endif
