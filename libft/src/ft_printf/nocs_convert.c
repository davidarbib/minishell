/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nocsp_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 21:56:22 by darbib            #+#    #+#             */
/*   Updated: 2020/01/21 00:45:49 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int			c_convert(t_buf *buf, t_conv *conv, va_list args)
{
	char filler;

	filler = ' ';
	if (conv->lmc < 1)
		conv->lmc = 1;
	if (conv->flags & ZERO)
		filler = '0';
	if (!(conv->flags & MINUS))
		fill_buffer(buf, conv->lmc - 1, filler);
	buf->s[buf->i++] = (char)va_arg(args, int);
	check_full(buf);
	filler = ' ';
	if (conv->flags & MINUS)
		fill_buffer(buf, conv->lmc - 1, filler);
	return (1);
}

static char	*init_s(char *filler, t_conv *conv, va_list args)
{
	*filler = ' ';
	if (conv->lmc < 1)
		conv->lmc = 0;
	if (conv->flags & ZERO)
		*filler = '0';
	return (va_arg(args, char *));
}

int			s_convert(t_buf *buf, t_conv *conv, va_list args)
{
	char	filler;
	char	*str;
	char	*substr;
	size_t	len;

	if (!(str = init_s(&filler, conv, args)))
		str = "(null)";
	len = ft_strlen(str);
	if (conv->flags & DOT && conv->prec < 0)
		conv->prec = len;
	if (!(conv->flags & DOT) || conv->prec > (signed int)len)
		conv->prec = len;
	if (!(conv->flags & MINUS) && conv->lmc > conv->prec)
		fill_buffer(buf, conv->lmc - conv->prec, filler);
	check_full(buf);
	if (!(substr = ft_substr(str, 0, conv->prec)))
		return (0);
	write_into(buf, &substr);
	if (conv->flags & MINUS && conv->lmc > conv->prec)
		fill_buffer(buf, conv->lmc - conv->prec, ' ');
	return (1);
}

int			no_convert(t_buf *buf, t_conv *conv, char c)
{
	char filler;

	filler = ' ';
	if (conv->lmc < 1)
		conv->lmc = 1;
	if (conv->flags & ZERO)
		filler = '0';
	if (!(conv->flags & MINUS))
		fill_buffer(buf, conv->lmc - 1, filler);
	buf->s[buf->i++] = c;
	check_full(buf);
	filler = ' ';
	if (conv->flags & MINUS)
		fill_buffer(buf, conv->lmc - 1, filler);
	return (1);
}
