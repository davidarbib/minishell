/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:49:37 by darbib            #+#    #+#             */
/*   Updated: 2020/01/15 22:45:12 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>
#include <limits.h>

static void	print_digits(int n, char *base, size_t *i, char *s_nb)
{
	char	tmp;
	int		base_len;

	base_len = ft_strlen(base);
	while ((n >= 1 && n > 0) || (n <= -1 && n < 0))
	{
		tmp = n % base_len;
		if (tmp < 0)
			tmp = tmp * -1;
		s_nb[*i] = base[(int)tmp];
		n /= base_len;
		(*i)--;
	}
}

char		*ft_itoa_base(int n, char *base)
{
	char	s_nb[12];
	char	sign;
	size_t	i;

	if (!base)
		return (NULL);
	sign = 0;
	if (n < 0)
		sign = 1;
	s_nb[11] = 0;
	i = 10;
	if (n == 0)
		s_nb[i--] = '0';
	print_digits(n, base, &i, s_nb);
	if (sign)
	{
		s_nb[i--] = '-';
	}
	return (ft_strdup(s_nb + i + 1));
}
