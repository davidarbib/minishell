/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:23:19 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/17 10:09:41 by fyusuf-a         ###   ########.fr       */
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

t_built_in g_built_in[6];

#endif
