/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sbuffer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 21:58:48 by darbib            #+#    #+#             */
/*   Updated: 2020/01/15 22:51:30 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"
#include "libft.h"
#include <unistd.h>

extern char	*g_buf_out;

void	buf_flush(t_buf *buf)
{
	ft_strlcat(g_buf_out, buf->s, BUFOUT_SIZE);
	ft_bzero(buf->s, BUF_SIZE);
	buf->count += buf->i;
	buf->i = 0;
}

void	check_full(t_buf *buf)
{
	if (buf->i == BUF_SIZE)
		buf_flush(buf);
}

void	init_buf(t_buf *buf)
{
	ft_bzero(buf->s, BUF_SIZE);
	ft_bzero(g_buf_out, BUFOUT_SIZE);
	buf->count = 0;
	buf->i = 0;
}

void	write_into(t_buf *buf, char **str)
{
	char *p_str;

	p_str = *str;
	while (*p_str)
	{
		buf->s[(buf->i)++] = *p_str++;
		check_full(buf);
	}
	free(*str);
	*str = NULL;
}

void	fill_buffer(t_buf *buf, size_t nb, char c)
{
	while (nb > 0)
	{
		buf->s[buf->i++] = c;
		check_full(buf);
		nb--;
	}
}
