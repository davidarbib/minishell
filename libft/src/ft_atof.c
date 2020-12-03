/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_mv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 19:43:18 by darbib            #+#    #+#             */
/*   Updated: 2020/03/02 19:55:09 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		handle_sign(char **str)
{
	int sign;

	sign = 1;
	while (**str && ft_isblank(**str))
		(*str)++;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static double	int_part(char **str, double f)
{
	while (**str && ft_isdigit(**str))
	{
		f *= 10;
		f += (double)(**str - '0');
		(*str)++;
	}
	return (f);
}

static double	float_part(char **str, double f)
{
	int div;

	div = 10;
	while (**str && ft_isdigit(**str))
	{
		f += (double)(**str - '0') / div;
		div *= 10;
		(*str)++;
	}
	return (f);
}

double			ft_atof(char *str)
{
	double	f;
	int		sign;

	f = 0.0;
	sign = handle_sign(&str);
	f = int_part(&str, f);
	if (*str == '.')
		str++;
	f = float_part(&str, f);
	return (sign * f);
}
