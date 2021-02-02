/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:05:34 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/02 13:24:51 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lookup(char* key, t_list *envlist)
{
	if (!envlist)
		return (NULL);
	if (ft_strcmp(((t_assignment *)envlist->content)->key, key) == 0)
		return (envlist);
	return (lookup(key, envlist->next));
}

t_list *insert(char* key, char* value, t_list *assignments)
{
	t_list			*index;
	t_assignment	*new_pair;

	if ((index = lookup(key, assignments)))
		((t_assignment *)index->content)->value = value;
	else
	{
		new_pair = malloc(sizeof(t_assignment));
	}
	return (assignments);
}

char	*ft_getenv(const char *name, t_list *envlist)
{

}
