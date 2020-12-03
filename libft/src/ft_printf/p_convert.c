/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_convert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 21:37:05 by darbib            #+#    #+#             */
/*   Updated: 2020/01/21 16:59:20 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*
** zero-filling inhibition by dot presence
** dot presence => default precision 0
*/

static unsigned long	init_ptr(t_conv *conv, va_list args)
{
	if ((conv->flags & ZERO) && (conv->flags & DOT) && (conv->prec >= 0))
		conv->flags -= ZERO;
	if (conv->prec < 0)
		conv->prec = 1;
	return ((unsigned long)va_arg(args, void *));
}

static void				prefield_one(t_buf *buf, t_conv *conv, size_t len)
{
	if (!(conv->flags & ZERO) && !(conv->flags & MINUS))
	{
		if (conv->prec > (signed int)len)
			len = conv->prec;
		if (conv->lmc > (signed int)len)
			fill_buffer(buf, conv->lmc - len, ' ');
	}
}

static void				prefield_two(t_buf *buf, t_conv *conv, size_t len)
{
	if (conv->flags & DOT && conv->prec > (signed int)len)
		fill_buffer(buf, conv->prec - len, '0');
	if (conv->flags & ZERO && conv->lmc > (signed int)len)
		fill_buffer(buf, conv->lmc - len, '0');
}

int						p_convert(t_buf *buf, t_conv *conv, va_list args)
{
	char			*str;
	unsigned long	ptr;
	size_t			len;

	ptr = init_ptr(conv, args);
	if (!(str = ft_ptoa(ptr)))
		return (0);
	len = ft_strlen(str) - (ptr == 0 && (conv->flags & DOT) && conv->prec == 0);
	prefield_one(buf, conv, len + 2);
	fill_buffer(buf, 1, '0');
	fill_buffer(buf, 1, 'x');
	prefield_two(buf, conv, len);
	if (!(ptr == 0 && (conv->flags & DOT) && conv->prec == 0))
	{
		write_into(buf, &str);
		check_full(buf);
	}
	if (conv->prec > (signed int)len)
		len = conv->prec;
	if (conv->flags & MINUS && conv->lmc > (signed int)len + 2)
		fill_buffer(buf, conv->lmc - (len + 2), ' ');
	return (1);
}
