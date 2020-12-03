/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:25:55 by darbib            #+#    #+#             */
/*   Updated: 2020/01/20 20:58:37 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdio.h>

int	(*g_convert[128])(t_buf*, t_conv*, va_list);

static void		init_conv(t_conv *conv)
{
	conv->lmc = 0;
	conv->prec = 0;
	conv->size = "default";
	conv->flags = 0;
}

static void		init_g_convert(void)
{
	g_convert[(int)'c'] = c_convert;
	g_convert[(int)'s'] = s_convert;
	g_convert[(int)'p'] = p_convert;
	g_convert[(int)'d'] = di_convert;
	g_convert[(int)'i'] = di_convert;
	g_convert[(int)'u'] = u_convert;
	g_convert[(int)'x'] = x_convert;
	g_convert[(int)'X'] = bigx_convert;
}

/*
** managing sizes
*/

static char		*conv_size(const char **format)
{
	if (**format == 'l' && *(*format + 1) == 'l')
	{
		*format += 2;
		return ("larger");
	}
	if (**format == 'h' && *(*format + 1) == 'h')
	{
		*format += 2;
		return ("shorter");
	}
	if (**format == 'l')
	{
		(*format)++;
		return ("large");
	}
	if (**format == 'h')
	{
		(*format)++;
		return ("short");
	}
	return ("default");
}

/*
** conversion input parsing to fill conversion state
*/

void			conv_parse(const char **format, va_list args, t_conv *conv)
{
	init_conv(conv);
	while (*(++*format))
	{
		if (!is_true_option(**format) && !ft_isdigit(**format))
			break ;
		add_option(**format, conv);
		if (ft_isdigit(**format))
			conv->lmc = atol_spe(format);
		if (**format == '*')
			conv->lmc = va_arg(args, int);
		if (**format == '.' && ft_isdigit(*(*format + 1)))
		{
			(*format)++;
			conv->prec = atol_spe(format);
		}
		if (**format == '.' && *(*format + 1) == '*')
		{
			(*format)++;
			conv->prec = va_arg(args, int);
		}
	}
	conv->size = conv_size(format);
}

/*
** if the conversion flag exists and is managed by current version
** of printf, the adequate processing function is called
** priority of minus over zero option flag is implemented here
*/

int				conv_make(const char **format, va_list args, t_conv *conv,
				t_buf *buf)
{
	if (star_post_process(conv) < 0)
		return (-1);
	if (conv->lmc > INTMAX)
		return (-1);
	init_g_convert();
	if ((conv->flags & MINUS) && (conv->flags & ZERO))
		conv->flags -= ZERO;
	if (ft_strchr(CONV_S, **format))
	{
		if (g_convert[(int)**format](buf, conv, args) == -1)
			return (-1);
	}
	if (!ft_strchr(FLAGS_S, **format)
		&& (ft_isalpha(**format) || (**format == '%')))
		no_convert(buf, conv, **format);
	(*format)++;
	return (0);
}
