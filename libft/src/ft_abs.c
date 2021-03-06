/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:56:37 by darbib            #+#    #+#             */
/*   Updated: 2020/08/09 18:30:10 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_abs(int x)
{
	if (x >= 0)
		return (x);
	else
		return (x * -1);
}

double	ft_double_abs(double x)
{
	if (x >= 0.0)
		return (x);
	else
		return (x * -1);
}
