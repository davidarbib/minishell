/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:43:58 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/16 11:57:33 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel_first(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	tmp = (*lst)->next;
	del((*lst)->content);
	free(*lst);
	*lst = tmp;
}
