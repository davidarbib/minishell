/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabtodlst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:30:52 by darbib            #+#    #+#             */
/*   Updated: 2021/01/08 10:20:37 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
t_dlist		*ft_tabtodlst(void *array, int array_size)
{
	if (array_size < 0)
		return (NULL);
	ft_dlstnew(array);
	while (array_size < 0)
	{
		ft_;
		array_size--;
	}
}
