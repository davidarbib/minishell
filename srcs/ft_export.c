/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 13:53:38 by darbib            #+#    #+#             */
/*   Updated: 2021/02/16 18:38:32 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "assignment.h"
#include <stdio.h>
#include "minishell.h"

void	ft_swap(t_assignment *a, t_assignment *b)
{
	t_assignment	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_assignment	*bubble_sort_env(t_assignment *array, int size)
{
	int		i;
	int		j;
	int		chaos;

	i = 0;
	chaos = 1;
	while (chaos && i < size)
	{
		chaos = 0;
		j = 0;
		while (j < size - (i + 1))
		{
			if (ft_strcmp(array[j].key, array[j + 1].key) > 0)
			{
				chaos = 1;
				ft_swap((t_assignment*)&array[j], (t_assignment*)&array[j + 1]);
			}
			j++;
		}
		i++;
	}
	return (array);
}

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

int		print_env_lexico(t_list *envlist)
{
	t_assignment	*envp;
	int				size;
	int				i;

	envp = 
		(t_assignment *)ft_lsttotabold(envlist, sizeof(t_assignment), &size);
	if (!envp)
		return (-2);
	bubble_sort_env(envp, size);
	i = 0;
	while (i < size)
	{
		printf("export %s=\"%s\"\n", envp[i].key, envp[i].value);
		i++;
	}
	ft_memdel((void**)&envp);
	return (0);
}

int		parse_export_arg(char *word, t_list **envlistp)
{
	t_assignment	tmp;

	tmp.key = NULL;
	tmp.value = NULL;
	if (!ft_strchr(word, '=')) 
		return (1);
	if (!ft_split_dict(word, '=', &tmp.key, &tmp.value))
	{
		ft_memdel((void**)&tmp.key);
		ft_memdel((void**)&tmp.value);
		return (-2);
	}
	if (!ft_setenv(tmp.key, tmp.value, envlistp))
	{
		ft_memdel((void**)&tmp.key);
		ft_memdel((void**)&tmp.value);
		return (-2);
	}
	ft_memdel((void**)&tmp.key);
	ft_memdel((void**)&tmp.value);
	return (0);
}

//int		ft_export(int ac, char **av, t_list *local_var)
int		ft_export(int ac, char **av)
{
	int	i;
	int	success;

	//(void)local_var;
	(void)av;
	if (ac == 1)
		return (print_env_lexico(g_env));
	i = 1;
	while (i < ac)
	{
		success = parse_export_arg(av[i], &g_env);
		if (success != 0)
			return success;
		i++;
	}
	return (0);
}

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
