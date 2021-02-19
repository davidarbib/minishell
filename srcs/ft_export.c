/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 13:53:38 by darbib            #+#    #+#             */
/*   Updated: 2021/02/19 11:33:14 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "assignment.h"
#include <stdio.h>
#include "minishell.h"

void			ft_swap(t_assignment *a, t_assignment *b)
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

int				print_env_lexico(t_list *envlist)
{
	t_assignment	*envp;
	int				size;
	int				i;

	envp = (t_assignment *)ft_lsttotabold(envlist, sizeof(t_assignment), &size);
	if (!envp)
		return (-2);
	bubble_sort_env(envp, size);
	i = 0;
	while (i < size)
	{
		ft_printf("export %s=\"%s\"\n", envp[i].key, envp[i].value);
		i++;
	}
	ft_memdel((void**)&envp);
	return (0);
}

int				parse_export_arg(char *word, t_list **envlistp)
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

int				ft_export(int ac, char **av, t_list **envlist)
{
	int	i;
	int	success;

	(void)envlist;
	(void)av;
	if (ac == 1)
		return (print_env_lexico(g_env));
	i = 1;
	while (i < ac)
	{
		if (!check_export_arg(av[i]))
			return (1);
		success = parse_export_arg(av[i], &g_env);
		if (success != 0)
			return (success);
		i++;
	}
	return (0);
}
