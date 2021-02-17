/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:40:09 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 00:17:55 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "environ.h"
#include "built_ins.h"
#include "error.h"
#include <stdio.h>

static int	travel(char *current_path, t_list **envlist)
{
	char	buf[BUFSIZE];

	if (!getcwd(buf, BUFSIZE))
		return (1);
	if (chdir(current_path) == -1)
		return (1);
	if (!ft_setenv("OLDPWD", buf, envlist))
		return (-2);
	if (!getcwd(buf, BUFSIZE))
		return (1);
	if (!ft_setenv("PWD", buf, envlist))
		return (-2);
	return (0);
}

static int	step_back(t_list **envlist)	
{
	char	*current_path;

	current_path = ft_getenv("OLDPWD", *envlist);
	if (!current_path)
	{
		ft_dprintf(2, "%s\n", ENOTOLDPWD);
		return (-1);
	}
	return (travel(current_path, envlist));
}

static int	to_home(t_list **envlist)
{
	char	*current_path;

	current_path = ft_getenv("HOME", *envlist);
	if (!current_path)
	{
		ft_dprintf(2, "%s\n", ENOTHOME);
		return (-1);
	}
	return (travel(current_path, envlist));
}

static int	normal_cd(char *dir_name, t_list **envlist)
{
	char	*current_path;

	current_path = dir_name;
	return (travel(current_path, envlist));
}

int	ft_cd(int ac, char **av, t_list **envlist)
{
	if (ac > 2)
		return (1);
	if (ac == 1)
		return (to_home(envlist));
	if (ft_strcmp(av[1], "-") == 0)
		return (step_back(envlist));
	else
		return (normal_cd(av[1], envlist));
	return (0);
}
