/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttotab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 22:04:16 by darbib            #+#    #+#             */
/*   Updated: 2020/08/09 18:31:21 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lsttotab(t_list *lst, size_t type_size, int *array_size)
{
	int				i;
	unsigned char	*array;

	*array_size = ft_lstsize(lst);
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
