/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttotab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 22:04:16 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 13:36:59 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	**ft_lsttotab(t_list *lst, size_t type_size, int *array_size)
{
	int				i;
	void			**array;

	*array_size = ft_lstsize(lst);
	if (!(array = ft_calloc((*array_size + 1), type_size)))
		return (NULL);
	i = 0;
	while (lst)
	{
		array[i] = lst->content;
		lst = lst->next;
		i++;
	}
	return ((void *)array);
}
