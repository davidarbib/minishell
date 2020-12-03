/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:22:31 by darbib            #+#    #+#             */
/*   Updated: 2020/02/09 18:34:57 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int nodes_nb;

	nodes_nb = 0;
	while (lst)
	{
		lst = lst->next;
		nodes_nb++;
	}
	return (nodes_nb);
}
