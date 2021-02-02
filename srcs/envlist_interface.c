/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:05:34 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/02 22:49:39 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"

void	replace_value(t_list *index, char *new_value)
{
	t_assignment	*pair;

	pair = (t_assignment *)index->content;
	ft_memdel((void **)&pair->value);
	pair->value = new_value;
}

t_list	*lookup(const char* key, t_list *envlist)
{
	if (!envlist)
		return (NULL);
	if (ft_strcmp(((t_assignment *)envlist->content)->key, key) == 0)
		return (envlist);
	return (lookup(key, envlist->next));
}

t_list *insert(char* key, char* value, t_list *envlist)
{
	t_list			*index;
	t_assignment	*new_pair;

	if ((index = lookup(key, envlist)))
		((t_assignment *)index->content)->value = value;
	else
	{
		new_pair = malloc(sizeof(t_assignment));
	}
	return (envlist);
}

char	*ft_getenv(const char *key, t_list *envlist)
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

int		ft_setenv(char *key, char *value, t_list **envlistp)
{
	t_assignment	pair;
	t_list			*index;

	pair.key = key;
	pair.value = value;
	if (!*envlistp)
	{
		if (!store_assignment(envlistp, &pair))
			return (0);
		return (1);
	}
	index = lookup(key, *envlistp);
	if (index)
		replace_value(index, value);
	else
	{
		if (!store_assignment(envlistp, &pair))
			return (0);
	}
	return (1);
}

/*
#include <string.h>
int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_list *envlist = to_environ_list(envp);
	ft_setenv(strdup("lolo"), strdup("lala"), &envlist);
	char *key = strdup("lolo");
	printf("$%s = %s\n", key, ft_getenv(key, envlist));
	ft_setenv(strdup("lolo"), strdup("lulu"), &envlist);
	printf("$%s = %s\n", key, ft_getenv(key, envlist));
	envlist = NULL;
	ft_setenv(strdup("lolo"), strdup("lili"), &envlist);
	printf("$%s = %s\n", key, ft_getenv(key, envlist));
	return (0);
}
*/

/*
#include <string.h>
int main(int ac, char **av, char **envp)
{
	if (ac != 2)
		return (1);
	char *key = strdup(av[1]);
	t_list *envlist = to_environ_list(envp);
	printf("%p\n", envlist);
	printf("$%s = %s\n", key, ft_getenv(key, envlist));
	return (0);
}
*/
