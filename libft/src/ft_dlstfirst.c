/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstfirst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:20:57 by darbib            #+#    #+#             */
/*   Updated: 2021/01/07 16:24:45 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	delete(void *content)
{
	free(content);
}

t_dlist	*ft_dlstfirst(t_dlist *lst)
{
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}

int main()
{
	t_dlist *head = ft_dlstnew(strdup("haha"));
	ft_dlstadd_back(&head, ft_dlstnew(strdup("test")));
	printf("head content : %s\n", head->content);
	printf("node content : %s\n", head->next->content);
	t_dlist *node = head->next;
	printf("head content (by node): %s\n", node->prev->content);
	printf("size of lst : %d\n", ft_dlstsize(head));
	t_dlist *first = ft_dlstfirst(node);
	printf("head content (by dlstfirst): %s\n", first->content);
	ft_dlstclear(&head, delete);
}
