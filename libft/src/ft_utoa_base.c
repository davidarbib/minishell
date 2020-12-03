/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:23:53 by darbib            #+#    #+#             */
/*   Updated: 2020/01/15 23:06:55 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>
#include <limits.h>

static void	print_digits(unsigned int n, char *base, size_t *i, char *s_nb)
{
	char	tmp;
	int		base_len;

	base_len = ft_strlen(base);
	while (n >= 1)
	{
		tmp = n % base_len;
		if (tmp < 0)
			tmp = tmp * -1;
		s_nb[*i] = base[(int)tmp];
		n /= base_len;
		(*i)--;
	}
}

char		*ft_utoa_base(unsigned int n, char *base)
{
	char	s_nb[12];
	size_t	i;

	if (!base)
		return (NULL);
	s_nb[11] = 0;
	i = 10;
	if (n == 0)
		s_nb[i--] = '0';
	print_digits(n, base, &i, s_nb);
	return (ft_strdup(s_nb + i + 1));
}
