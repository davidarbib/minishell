/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 19:05:40 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/16 11:16:55 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void				ft_lstremove_if(t_list **alst, void *data_ref,
						int (*cmp)(), void free_fct(void *))
{
	if (!alst)
		return ;
	if (!(*alst))
		return ;
	if (cmp((*alst)->content, data_ref) == 0)
	{
		free_fct((*alst)->content);
		if ((*alst)->next)
			*alst = (*alst)->next;
		else
		{
			*alst = NULL;
			return ;
		}
	}
	ft_lstremove_if(&(*alst)->next, data_ref, cmp, free_fct);
}
