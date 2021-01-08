/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabtodlst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:30:52 by darbib            #+#    #+#             */
/*   Updated: 2021/01/08 16:32:20 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*make_content(void *array_ptr, int type_size)
{
	void *content;

	if (!((content = ft_calloc(1, typesize))))
		return (NULL);
	ft_memmove(content, array_ptr, typesize);
	return (content);
}

static void	delete_content(void *content)
{
	free(content);
}

static int	add_node(t_dlst **alst, void *array, int typesize)
{
	t_dslt	*node;

	if (!(tmp_content = make_content(array, type_size)))
	{
		ft_dlstclear(&head, delete_content)
			return (0);
	}
	if (!(node = ft_dlstnew(tmp_content)))
	{
		ft_dlstclear(&head, delete_content)
			return (0);
	}
	ft_dlstadd_back(&head, node);
	return (1);
}

t_dlist		*ft_tabtodlst(void *array, int array_size, int type_size)
{
	int		i;
	t_dlst	*head;
	void	*tmp_content;

	if (array_size < 0)
		return (NULL);
	if (!(tmp_content = make_content(array, type_size)))
		return (NULL);
	head = ft_dlstnew();
	while (i < array_size)
	{
		add_node(&head, (array + i * typesize), typesize);
		i++;
	}
}
