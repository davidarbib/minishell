/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabtodlst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:30:52 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 13:17:35 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	*make_content(void *array_ptr, int type_size)
{
	void *content;

	if (!(content = ft_calloc(1, type_size)))
		return (NULL);
	ft_memmove(content, array_ptr, type_size);
	return (content);
}

static void	delete_content(void *content)
{
	free(content);
}

static int	add_node(t_dlist **alst, void *array, int type_size)
{
	t_dlist	*node;
	void	*tmp_content;

	if (!(tmp_content = make_content(array, type_size)))
	{
		ft_dlstclear(alst, delete_content);
		return (0);
	}
	if (!(node = ft_dlstnew(tmp_content)))
	{
		ft_dlstclear(alst, delete_content);
		return (0);
	}
	ft_dlstadd_back(alst, node);
	return (1);
}

t_dlist		*ft_tabtodlst(void *array, int array_size, int type_size)
{
	int		i;
	t_dlist	*head;
	void	*tmp_content;

	if (array_size < 1)
		return (NULL);
	if (!(tmp_content = make_content(array, type_size)))
		return (NULL);
	head = ft_dlstnew(tmp_content);
	i = 1;
	while (i < array_size)
	{
		if (!(add_node(&head, (array + i * type_size), type_size)))
			return (NULL);
		i++;
	}
	return (head);
}
