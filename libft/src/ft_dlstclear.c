/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 23:05:52 by darbib            #+#    #+#             */
/*   Updated: 2021/01/28 21:54:43 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	ft_dlstclear(t_dlist **lst, void (*del)(void*))
{
	t_dlist	*head;
	t_dlist	*tmp;

	head = *lst;
	while (head)
	{
		tmp = head->next;
		(*del)(head->content);
		ft_memdel((void **)&head);
		head = tmp;
	}
	lst = NULL;
}
