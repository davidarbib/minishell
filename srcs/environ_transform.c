/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_transform.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:31:38 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 13:19:54 by darbib           ###   ########.fr       */
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
