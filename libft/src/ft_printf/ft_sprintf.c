/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 20:47:08 by darbib            #+#    #+#             */
/*   Updated: 2020/01/15 22:50:34 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

char		*g_buf_out;

int			ft_sprintf(char *buf_out, const char *format, ...)
{
	va_list args;
	t_buf	buf;
	t_conv	conv;

	g_buf_out = buf_out;
	if (!format || !*format)
		return (0);
	va_start(args, format);
	init_buf(&buf);
	while (*format)
	{
		if (*format != '%')
			buf.s[buf.i++] = *(format++);
		else
		{
			buf_flush(&buf);
			conv_parse(&format, args, &conv);
			if ((conv_make(&format, args, &conv, &buf)) < 0)
				return (-1);
		}
		check_full(&buf);
	}
	buf_flush(&buf);
	va_end(args);
	return (buf.count);
}
