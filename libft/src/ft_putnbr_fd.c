/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:53:16 by darbib            #+#    #+#             */
/*   Updated: 2019/11/06 20:40:58 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
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
	write(fd, s_nb + i + 1, 10 - i);
}
