/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_elem.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 11:29:15 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/01/31 19:56:49 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_lstadd_back_elem(t_list **alst, void *data)
{
	t_list *new;

	if (!(new = malloc(sizeof(t_list))))
		return (1);
	new->content = data;
	new->next = NULL;
	if (*alst == NULL)
		*alst = new;
	else
		ft_lstadd_back(alst, new);
	return (0);
}
