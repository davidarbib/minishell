/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 11:48:01 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 11:48:16 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "obj_destructor.h"
#include <string.h>
int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_list *envlist = to_environ_list(envp);
	ft_setenv("lolo", "lala", &envlist);
	char *key = "lolo";
	printf("$%s = %s\n", key, ft_getenv(key, envlist));
	ft_setenv("lolo", "lulu", &envlist);
	printf("$%s = %s\n", key, ft_getenv(key, envlist));
	ft_lstclear(&envlist, del_assign_content);
	envlist = NULL;
	printf("$%s = %s\n", key, ft_getenv(key, envlist));
	ft_setenv("lolo", "lili", &envlist);
	printf("$%s = %s\n", key, ft_getenv(key, envlist));
	ft_lstclear(&envlist, del_assign_content);
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
