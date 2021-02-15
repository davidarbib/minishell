/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_strict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 19:36:16 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/12 22:24:45 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_atoi_strict(const char *str)
{
	int number;
	int	sign;

	number = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		number = 10 * number + (*str - '0');
		str++;
	}
	return (sign * number);
}
