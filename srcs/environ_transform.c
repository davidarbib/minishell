/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_transform.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:31:38 by darbib            #+#    #+#             */
/*   Updated: 2021/02/01 21:43:06 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "assignment.h"
#include "obj_destructor.h"

t_list	*to_environ_list(char **environ)
{
	int				i;
	t_assignment	envvar;
	t_list			*environ_list;

	i = 0;
	while (environ[i])
	{
		envvar.key = NULL;
		envvar.value = NULL;
		if (!ft_split_dict(environ[i], '=', &envvar.key, &envvar.value))
		{
			destroy_assignment(&envvar);
			return (NULL);
		}
		if (!store_assignment(&environ_list, &envvar))
		{
			destroy_assignment(&envvar);
			ft_lstclear(&environ_list, del_assign_content);
			return (NULL);
		}
		i++;
	}
	return (environ_list);
}

char	*ft_getenv(const char *name, t_list *envlist)
{
}

/*
#include "environ.h"

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_list *env_list = to_environ_list(envp);

	t_list *node = env_list;
	while (node)
	{
		t_assignment *var = (t_assignment *)node->content;
		printf("%s=%s\n", var->key, var->value); 
		node = node->next;
	}
}
*/
