/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 21:23:13 by darbib            #+#    #+#             */
/*   Updated: 2021/01/07 15:23:50 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

void	ft_dlstadd_back(t_dlist **alst, t_dlist *new)
{
	t_dlist *node;

	node = *alst;
	while (node->next)
		node = node->next;
	node->next = new;
	new->prev = node;
}
