/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:13:20 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 00:14:03 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
#include <stdio.h>
int main()
{
	char **array = calloc(4, sizeof(char *));
	array[2] = ft_strdup("aaa");
	array[1] = ft_strdup("bbb");
	array[3] = ft_strdup("ccc");
	array[0] = ft_strdup("ddd");
	int i = 0;
	while (i < 4)
		printf("%s\n", array[i++]);
	bubble_sort_str_array(array, 4);
	printf("--------------------\n");
	i = 0;
	while (i < 4)
		printf("%s\n", array[i++]);
	free(array[0]);
	free(array[1]);
	free(array[2]);
	free(array[3]);
	free(array);
	return (0);
}
*/
/*
#include <string.h>
#include "obj_destructor.h"
#include "environ.h"

int main(int ac, char **av, char **envp)
{
	t_list *node;

	(void)ac;
	(void)av;
	g_env = to_environ_list(envp);
	node = g_env;
	while (node)
	{
		t_assignment *tmp;
		tmp = (t_assignment*)node->content;
		printf("export : %s=\"%s\"\n", tmp->key, tmp->value);
		node = node->next;
	}
	return (0);
}
*/
/*
#include <string.h>
#include "obj_destructor.h"
#include "environ.h"

int main(int ac, char **av, char **envp)
{
	g_env = to_environ_list(envp);
	ft_export(ac, av);
	printf("a=%s\n", ft_getenv("a", g_env));
	printf("d=%s\n", ft_getenv("d", g_env));
	ft_lstclear(&g_env, del_assign_content);
	return (0);
}
*/
