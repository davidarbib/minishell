/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:40:09 by darbib            #+#    #+#             */
/*   Updated: 2021/02/10 12:19:01 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environ.h"
#include "built_ins.h"
#include "error.h"
#include <stdio.h>

static int	travel(char *current_path, t_list **envlist)
{
	char	buf[BUFSIZE];
	
	if (!getcwd(buf, BUFSIZE))
		return (-1);
	if (chdir(current_path) == -1)
		return (-1);
	if (!ft_setenv("OLDPWD", buf, envlist))
		return (-2);
	if (!getcwd(buf, BUFSIZE))
		return (-1);
	if (!ft_setenv("PWD", buf, envlist))
		return (-2);
	return (1);
}

int	step_back(t_list **envlist)	
{
	char	*current_path;

	current_path = ft_getenv("OLDPWD", *envlist);
	if (!current_path)
	{
		printf("%s\n", ENOTOLDPWD);
		return (0);
	}
	return (travel(current_path, envlist));
}

int	to_home(t_list **envlist)
{
	char 	*current_path;

	current_path = ft_getenv("HOME", *envlist);
	if (!current_path)
	{
		printf("%s\n", ENOTHOME);
		return (0);
		//set shell_errno?
	}
	return (travel(current_path, envlist));
}

int	normal_cd(char *dir_name, t_list **envlist)
{
	char 	*current_path;

	current_path = dir_name;
	return (travel(current_path, envlist));
}

int	ft_cd(int ac, char **av, t_list **envlist)
{
	if (ac > 2)
		return (0);
	if (ac == 1)
		return (to_home(envlist));
	if (ft_strcmp(av[1], "-") == 0)
		return (step_back(envlist));	
	else
		return (normal_cd(av[1], envlist));
	return (1);
}

/*
#include "obj_destructor.h"
int main(int ac, char **av, char **envp)
{
	t_list *envlist = to_environ_list(envp);
	char buf[BUFSIZE];
	getcwd(buf, BUFSIZE);
	printf("current dir : %s\n", buf);
	if ((ft_cd(ac, av, &envlist) < 0))
	{
		perror("cd");
		ft_lstclear(&envlist, del_assign_content);
		return (1);
	}
	getcwd(buf, BUFSIZE);
	printf("current dir : %s\n", buf);
	printf("pwd in list : %s\n", ft_getenv("PWD", envlist));
	printf("oldpwd in list : %s\n", ft_getenv("OLDPWD", envlist));
	ft_lstclear(&envlist, del_assign_content);
	return (0);
}
*/
