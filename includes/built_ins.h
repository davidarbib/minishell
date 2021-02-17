/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:23:19 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/16 19:04:53 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "libft.h"

# define BUFSIZE 8192

# define BUILT_IN_NUMBER 6

int		ft_cd(int ac, char **av, t_list **envlist);
int		ft_echo(int ac, char **av, t_list **envlist);
int		ft_pwd(void);
int		ft_exit(int ac, char **av, t_list **envlist);
int		ft_env(int ac, char **av, t_list **envlist);
int		ft_unset(int ac, char **av, t_list **envlist);

typedef struct	s_built_in {
	char		*name;
	int			(*handler)();
}				t_built_in;

t_built_in g_built_in[6] = {
	{
		.name = "cd",
		.handler = ft_cd
	},
	{
		.name = "echo",
		.handler = ft_echo
	},
	{
		.name = "env",
		.handler = ft_env
	},
	{
		.name = "unset",
		.handler = ft_unset
	},
	{
		.name = "exit",
		.handler = ft_exit
	},
	{
		.name = "pwd",
		.handler = ft_pwd
	}
};

#endif
