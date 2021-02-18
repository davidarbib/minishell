/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 11:42:59 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 11:43:37 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"

char	*lookup_value(const char *key, t_list *envlist)
{
	if (!envlist)
		return (NULL);
	if (ft_strcmp(((t_assignment *)envlist->content)->key, key) == 0)
		return (((t_assignment*)envlist->content)->value);
	return (lookup_value(key, envlist->next));
}
