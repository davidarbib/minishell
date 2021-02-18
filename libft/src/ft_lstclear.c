/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 23:05:52 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 19:29:06 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*head;
	t_list	*tmp;

	head = *lst;
	while (head)
	{
		tmp = head->next;
		(*del)(head->content);
		ft_memdel((void**)&head);
		head = tmp;
	}
	*lst = NULL;
}
