/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 19:05:40 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/21 14:55:26 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_list				*ft_lstremove_if_acc(t_list **alst, void *data_ref,
						int (*cmp)(), void free_fct(void *))
{
	t_list	*tmp;

	tmp = *alst;
	if (!(*alst))
		return (NULL);
	if (cmp((*alst)->content, data_ref) == 0)
	{
		free_fct((*alst)->content);
		tmp = *alst;
		*alst = (*alst)->next;
		free(tmp);
		*alst = ft_lstremove_if_acc(alst, data_ref, cmp, free_fct);
		return (*alst);
	}
	(*alst)->next = ft_lstremove_if_acc(&((*alst)->next),
							data_ref, cmp, free_fct);
	return (*alst);
}

void				ft_lstremove_if(t_list **alst, void *data_ref,
						int (*cmp)(), void free_fct(void *))
{
	if (!alst)
		return ;
	ft_lstremove_if_acc(alst, data_ref, cmp, free_fct);
}
