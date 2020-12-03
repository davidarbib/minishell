/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 21:56:11 by darbib            #+#    #+#             */
/*   Updated: 2020/04/13 00:34:10 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_utoa(unsigned int n)
{
	char	s_nb[12];
	size_t	i;
	char	tmp;

	s_nb[11] = 0;
	i = 10;
	if (n == 0)
		s_nb[i--] = '0';
	while (n >= 1 && n > 0)
	{
		tmp = n % 10;
		if (tmp < 0)
			tmp = tmp * -1;
		s_nb[i] = tmp + '0';
		n /= 10;
		i--;
	}
	return (ft_strdup(s_nb + i + 1));
}
