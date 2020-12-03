/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 22:27:42 by darbib            #+#    #+#             */
/*   Updated: 2020/01/18 19:33:41 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		atoi_spe(const char **str)
{
	long long	nb;
	signed char	sign;

	nb = 0;
	sign = 1;
	while (**str && (**str == '\f' || **str == '\t' || **str == ' '
			|| **str == '\n' || **str == '\r' || **str == '\v'))
		(*str)++;
	if ((**str == '+' || **str == '-') && ft_isdigit(*(*str + 1)))
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	while (**str && ft_isdigit(**str))
		nb = nb * 10 + *(*str)++ - '0';
	(*str)--;
	return (sign * nb);
}

long	atol_spe(const char **str)
{
	long long	nb;
	signed char	sign;

	nb = 0;
	sign = 1;
	while (**str && (**str == '\f' || **str == '\t' || **str == ' '
			|| **str == '\n' || **str == '\r' || **str == '\v'))
		(*str)++;
	if ((**str == '+' || **str == '-') && ft_isdigit(*(*str + 1)))
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	while (**str && ft_isdigit(**str))
		nb = nb * 10 + *(*str)++ - '0';
	(*str)--;
	return ((long)(sign * nb));
}

void	add_option(char c, t_conv *conv)
{
	char	*s;
	char	*p_s;
	int		option;

	s = OPTS_MY;
	if ((p_s = ft_strchr(s, c)))
	{
		option = 1 << (p_s - s);
		if (!(conv->flags & option))
			conv->flags += option;
	}
}

char	is_true_option(char c)
{
	if (ft_strchr(OPTS_TRUE, c))
		return (1);
	return (0);
}

int		star_post_process(t_conv *conv)
{
	if (conv->lmc == INTMIN)
		return (-1);
	if (conv->lmc < 0)
	{
		conv->lmc *= -1;
		if (!(conv->flags & MINUS))
			conv->flags += MINUS;
	}
	return (0);
}
