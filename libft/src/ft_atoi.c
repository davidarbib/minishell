/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:12:32 by darbib            #+#    #+#             */
/*   Updated: 2020/02/10 22:20:43 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_atoi(const char *str)
{
	long long	nb;
	signed char	sign;

	nb = 0;
	sign = 1;
	while (*str && (*str == '\f' || *str == '\t' || *str == ' ' || *str == '\n'
			|| *str == '\r' || *str == '\v'))
		str++;
	if ((*str == '+' || *str == '-') && ft_isdigit(*(str + 1)))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
		nb = nb * 10 + *str++ - '0';
	return (sign * nb);
}
