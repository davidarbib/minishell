/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 21:35:58 by darbib            #+#    #+#             */
/*   Updated: 2020/01/21 17:02:28 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*
** zero-filling inhibition by dot presence
** dot presence => default precision 0
*/

static char	init_sign_nb(t_conv *conv, va_list args, int *nb)
{
	if ((conv->flags & ZERO) && (conv->flags & DOT) && (conv->prec >= 0))
		conv->flags -= ZERO;
	if (conv->prec < 0)
		conv->prec = 1;
	*nb = va_arg(args, int);
	return (*nb < 0);
}

static void	prefield_one(t_buf *buf, t_conv *conv, size_t len, char sign)
{
	if (!(conv->flags & ZERO) && !(conv->flags & MINUS))
	{
		if ((conv->prec + sign) > (signed int)len)
			len = conv->prec + sign;
		if (conv->lmc > (signed int)len)
			fill_buffer(buf, conv->lmc - len, ' ');
	}
}

static void	prefield_two(t_buf *buf, t_conv *conv, size_t len, char sign)
{
	if (conv->flags & DOT && conv->prec > ((signed int)len - sign))
		fill_buffer(buf, conv->prec - (len - sign), '0');
	if (conv->flags & ZERO && conv->lmc > (signed int)len)
		fill_buffer(buf, conv->lmc - len, '0');
}

static char	radical(t_buf *buf, char **p_str, char sign, size_t len)
{
	char	*substr;

	if (!(substr = ft_substr(*p_str, sign, len - sign)))
		return (0);
	free(*p_str);
	*p_str = NULL;
	write_into(buf, &substr);
	check_full(buf);
	return (1);
}

int			di_convert(t_buf *buf, t_conv *conv, va_list args)
{
	char	*str;
	char	sign;
	int		nb;
	size_t	len;

	sign = init_sign_nb(conv, args, &nb);
	if (!(str = ft_itoa(nb)))
		return (0);
	len = ft_strlen(str) - (nb == 0 && conv->flags & DOT && conv->prec == 0);
	prefield_one(buf, conv, len, sign);
	if (sign)
		fill_buffer(buf, 1, '-');
	prefield_two(buf, conv, len, sign);
	if (!(nb == 0 && conv->flags & DOT && conv->prec == 0))
	{
		if (!radical(buf, &str, sign, len))
			return (0);
	}
	if ((conv->prec + sign) > (signed int)len)
		len = conv->prec + sign;
	if (conv->flags & MINUS && conv->lmc > (signed int)len)
		fill_buffer(buf, conv->lmc - len, ' ');
	return (1);
}
