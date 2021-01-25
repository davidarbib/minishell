/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:05:34 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/01/25 13:40:04 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lookup(char* key, t_list *assignments)
{
	if (!assignements)
		return (NULL);
	if (ft_strcmp(assignments->content->key, key) == 0)
		return (assignment)
	return (lookup(key, assignments->next));
}

t_list *insert(char* key, char* value, t_list *assignments)
{
	t_list			*index;
	t_assignment	*new_pair;
	if ((index = lookup(key, assignments))
		index->content->value = value;
	else
	{
		new_pair = malloc(sizeof(t_assignment));
	}
	return (assignments);
	

}
