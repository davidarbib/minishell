/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_init_and_tools.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 22:53:47 by darbib            #+#    #+#             */
/*   Updated: 2021/02/14 22:54:30 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_quote_removal.h"

int		add_char_to_buffer(char *buf, size_t *size, size_t *count, char c)
{
	if ((size_t)(*count) + 1 == *size)
	{
		buf = (char *)ft_realloc(buf, *size, *size * 2);
		if (!buf)
			return (0);
		*size *= 2;
	}
	buf[*count] = c;
	(*count)++;
	return (1);
}

int		init_expansion(t_expand *fsm) 
{
	fsm->state = base_state;
	fsm->search_buf_size = DEFAULT_BUFSIZE;
	fsm->result_buf_size = DEFAULT_BUFSIZE;
	fsm->search_buf = NULL;
	fsm->result_buf = NULL;
	fsm->search_buf = (char *)ft_calloc(fsm->search_buf_size, sizeof(char));
	fsm->result_buf = (char *)ft_calloc(fsm->result_buf_size, sizeof(char));
	fsm->search_buf_count = 0;
	fsm->result_buf_count = 0;
	if (fsm->search_buf && fsm->result_buf)
		return (1);
	return (0);
}
