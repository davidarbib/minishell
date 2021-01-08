/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlsttotab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 22:04:16 by darbib            #+#    #+#             */
/*   Updated: 2021/01/08 10:07:05 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_dlsttotab(t_dlist *lst, size_t type_size, int *array_size)
{
	int				i;
	unsigned char	*array;

	*array_size = ft_dlstsize(lst);
	if (!(array = ft_calloc((*array_size + 1), type_size)))
		return (NULL);
	i = 0;
	while (lst)
	{
		ft_memmove(array + i, (const void *)lst->content, type_size);
		lst = lst->next;
		i += type_size;
	}
	return ((void *)array);
}
