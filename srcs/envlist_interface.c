/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:05:34 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/18 11:50:21 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"

static int	replace_value(t_list *index, char *new_value)
{
	t_assignment	*pair;

	pair = (t_assignment *)index->content;
	ft_memdel((void **)&pair->value);
	pair->value = ft_strdup(new_value);
	if (!pair->value)
		return (0);
	return (1);
}

static int	append_env(t_assignment *pair, t_list **envlistp)
{
	pair->key = ft_strdup(pair->key);
	pair->value = ft_strdup(pair->value);
	if (!(pair->value && pair->key))
		return (0);
	if (!store_assignment(envlistp, pair))
	{
		ft_memdel((void **)&pair->key);
		ft_memdel((void **)&pair->value);
		return (0);
	}
	return (1);
}

t_list		*lookup(const char *key, t_list *envlist)
{
	if (!envlist)
		return (NULL);
	if (ft_strcmp(((t_assignment *)envlist->content)->key, key) == 0)
		return (envlist);
	return (lookup(key, envlist->next));
}

char		*ft_getenv(const char *key, t_list *envlist)
{
	t_assignment	*pair;
	t_list			*node;

	if (!envlist)
		return (NULL);
	node = lookup(key, envlist);
	if (!node)
		return (NULL);
	pair = (t_assignment *)node->content;
	return (pair->value);
}

int			ft_setenv(char *key, char *value, t_list **envlistp)
{
	t_assignment	pair;
	t_list			*index;

	pair.key = key;
	pair.value = value;
	if (!*envlistp)
	{
		if (!append_env(&pair, envlistp))
			return (0);
		return (1);
	}
	index = lookup(key, *envlistp);
	if (index)
	{
		if (!replace_value(index, value))
			return (0);
	}
	else
	{
		if (!append_env(&pair, envlistp))
			return (0);
	}
	return (1);
}
