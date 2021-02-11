/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_removal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:26:18 by darbib            #+#    #+#             */
/*   Updated: 2021/02/11 22:55:14 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_QUOTE_REMOVAL_H
# define EXPAND_QUOTE_REMOVAL_H

# include <stdlib.h>
# include "environ.h"
# include "libft.h"

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
	char	*search_buf;
	char	*result_buf;
	size_t	search_buf_size;
	size_t	result_buf_size;
	size_t	search_buf_count;
	size_t	result_buf_count;
	int		state;
	char	current_char;
}				t_expand;

extern t_list	*g_env;

int		add_char_to_buffer(char *buf, size_t *size, size_t *count, char c);
int		copy_to_search_buffer(t_expand *fsm);
int		copy_to_result_buffer(t_expand *fsm);
int		fetch_env_var(t_expand *fsm);
#endif
