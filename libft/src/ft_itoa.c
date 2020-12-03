/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:58:58 by darbib            #+#    #+#             */
/*   Updated: 2019/12/09 16:20:57 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_itoa(int n)
{
	char	s_nb[12];
	char	sign;
	size_t	i;
	char	tmp;

	sign = 0;
	if (n < 0)
		sign = 1;
	s_nb[11] = 0;
	i = 10;
	if (n == 0)
		s_nb[i--] = '0';
	while ((n >= 1 && n > 0) || (n <= -1 && n < 0))
	{
		tmp = n % 10;
		if (tmp < 0)
			tmp = tmp * -1;
		s_nb[i] = tmp + '0';
		n /= 10;
		i--;
	}
	if (sign)
		s_nb[i--] = '-';
	return (ft_strdup(s_nb + i + 1));
}
