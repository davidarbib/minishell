/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_convert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:15:44 by darbib            #+#    #+#             */
/*   Updated: 2020/04/13 00:32:42 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*
** zero-filling inhibition by dot presence
** dot presence => default precision 0
*/

static void	init_nb(t_conv *conv, va_list args, unsigned int *nb)
{
	if ((conv->flags & ZERO) && (conv->flags & DOT) && (conv->prec >= 0))
		conv->flags -= ZERO;
	if (conv->prec < 0)
		conv->prec = 1;
	*nb = va_arg(args, unsigned int);
}

static void	prefield_one(t_buf *buf, t_conv *conv, size_t len)
{
	if (!(conv->flags & ZERO) && !(conv->flags & MINUS))
	{
		if (conv->prec > (signed int)len)
			len = conv->prec;
		if (conv->lmc > (signed int)len)
			fill_buffer(buf, conv->lmc - len, ' ');
	}
}

static void	prefield_two(t_buf *buf, t_conv *conv, size_t len)
{
	if (conv->flags & DOT && conv->prec > (signed int)len)
		fill_buffer(buf, conv->prec - len, '0');
	if (conv->flags & ZERO && conv->lmc > (signed int)len)
		fill_buffer(buf, conv->lmc - len, '0');
}

int			x_convert(t_buf *buf, t_conv *conv, va_list args)
{
	char			*str;
	unsigned int	nb;
	size_t			len;

	init_nb(conv, args, &nb);
	if (!(str = ft_utoa_base(nb, LOWERHEX)))
		return (0);
	len = ft_strlen(str) - (nb == 0 && (conv->flags & DOT) && conv->prec == 0);
	prefield_one(buf, conv, len);
	prefield_two(buf, conv, len);
	if (!(nb == 0 && (conv->flags & DOT) && conv->prec == 0))
	{
		write_into(buf, &str);
		check_full(buf);
	}
	if (conv->prec > (signed int)len)
		len = conv->prec;
	if (conv->flags & MINUS && conv->lmc > (signed int)len)
		fill_buffer(buf, conv->lmc - len, ' ');
	return (1);
}

int			bigx_convert(t_buf *buf, t_conv *conv, va_list args)
{
	char			*str;
	unsigned int	nb;
	size_t			len;

	init_nb(conv, args, &nb);
	if (!(str = ft_utoa_base(nb, UPPERHEX)))
		return (0);
	len = ft_strlen(str) - (nb == 0 && (conv->flags & DOT) && conv->prec == 0);
	prefield_one(buf, conv, len);
	prefield_two(buf, conv, len);
	if (!(nb == 0 && (conv->flags & DOT) && conv->prec == 0))
	{
		write_into(buf, &str);
		check_full(buf);
	}
	if (conv->prec > (signed int)len)
		len = conv->prec;
	if (conv->flags & MINUS && conv->lmc > (signed int)len)
		fill_buffer(buf, conv->lmc - len, ' ');
	return (1);
}
