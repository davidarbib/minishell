/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 19:05:40 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/01 12:26:38 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void				*ft_lstfind_content(t_list *alst, void *data_ref,
						int (*cmp)())
{
	if (!alst)
		return (NULL);
	if (cmp(alst->content, data_ref) == 0)
		return (alst->content);
	return (ft_lstfind_content(alst->next, data_ref, cmp));
}
