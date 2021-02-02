/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:40:09 by darbib            #+#    #+#             */
/*   Updated: 2021/02/02 23:56:05 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environ.h"
#include "ft_cd.h"

int	step_back(t_list *envlist)	
{
	char *current_path;
	char *new_pwd_value;
	char *new_pwd_key;

	current_path = ft_getenv("OLDPWD", envlist);
	if (!current_path)
		//set shell_errno?
		return (0);
	chdir(current_path);
	//check NULL
	new_pwd_value = ft_strdup(current_path);
	if (!new_pwd)
		return (-1);
	ft_setenv("PWD", new_pwd);
	return (1);
}

int	to_home(t_list *envlist)
{
	char *current_path;

	current_path = ft_getenv("HOME", envlist);
	if (!current_path)
		//set shell_errno?
		return (0);
	chdir(current_path);
	//check NULL
	//set pwd and oldpwd	
	return (1);
}

int	ft_cd(int ac, char **av, t_list *envlist)
{
	if (ac > 2)
		return (0);
	if (ac == 1)
		to_home(envlist);
	if (ft_strcmp(av[1], "-") == 0)
		step_back(envlist);	
	return (1);
}
