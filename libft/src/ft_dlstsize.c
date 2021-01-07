/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:22:31 by darbib            #+#    #+#             */
/*   Updated: 2021/01/07 16:26:43 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

int	ft_dlstsize(t_dlist *lst)
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
