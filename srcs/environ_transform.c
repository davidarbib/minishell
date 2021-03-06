/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_transform.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:31:38 by darbib            #+#    #+#             */
/*   Updated: 2021/02/20 13:56:19 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "assignment.h"
#include "obj_destructor.h"

t_list	*to_environ_list(char **envp)
{
	int				i;
	t_assignment	envvar;
	t_list			*environ_list;

	i = 0;
	environ_list = NULL;
	while (envp[i])
	{
		envvar.key = NULL;
		envvar.value = NULL;
		if (!ft_split_dict(envp[i], '=', &envvar.key, &envvar.value))
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

char	**to_environ_array(t_list *environ)
{
	int		l;
	int		l1;
	int		l2;
	int		i;
	char	**ret;

	l = ft_lstsize(environ);
	if (!(ret = malloc((l + 1) * sizeof(char*))))
		return (NULL);
	ret[l] = 0;
	i = 0;
	while (i < l)
	{
		l1 = ft_strlen(((t_assignment*)environ->content)->key);
		l2 = ft_strlen(((t_assignment*)environ->content)->value);
		ret[i] = malloc(l1 + l2 + 2);
		ft_strlcpy(ret[i], ((t_assignment*)environ->content)->key, l1 + 1);
		ret[i][l1] = '=';
		ret[i][l1 + 1] = '\0';
		ft_strlcat(ret[i],
				((t_assignment*)environ->content)->value, l1 + l2 + 2);
		i++;
		environ = environ->next;
	}
	return (ret);
}
