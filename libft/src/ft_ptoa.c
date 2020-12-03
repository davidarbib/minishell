/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 22:47:45 by darbib            #+#    #+#             */
/*   Updated: 2020/04/13 00:36:46 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>
#include <limits.h>

static void	print_digits(unsigned long n, int base, size_t *i, char *s_nb)
{
	char	tmp;
	char	*s_base;

	s_base = "0123456789abcdef";
	while (n >= 1)
	{
		tmp = n % base;
		if (tmp < 0)
			tmp = tmp * -1;
		s_nb[*i] = s_base[(int)tmp];
		n /= base;
		(*i)--;
	}
}

char		*ft_ptoa(unsigned long ptr)
{
	char	s_nb[16];
	size_t	i;

	s_nb[15] = 0;
	i = 14;
	if (ptr == 0)
		s_nb[i--] = '0';
	print_digits(ptr, 16, &i, s_nb);
	return (ft_strdup(s_nb + i + 1));
}
