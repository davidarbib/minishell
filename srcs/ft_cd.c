/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:40:09 by darbib            #+#    #+#             */
/*   Updated: 2021/02/01 22:53:26 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environ.h"

int	step_back(t_list *envlist)	
{
	char *current_path;

	current_path = ft_getenv("OLDPWD", envlist);
	//check NULL
	chdir(current_path);
	//check NULL
	//set pwd and oldpwd	
	return (1);
}

int	to_home(t_list *envlist)
{
	char *current_path;

	current_path = ft_getenv("HOME", envlist);
	//check NULL
	chdir(current_path);
	//check NULL
	//set pwd and oldpwd	
	return (1);
}

int	ft_cd(int ac, char **av, t_list *envlist)
{

	if (ac > 2)
		return (-1);
	if (ac == 1)
		to_home(envlist);
	if (ft_strcmp(av[1], "-") == 0)
		step_back(envlist);	
	return (1);
}
