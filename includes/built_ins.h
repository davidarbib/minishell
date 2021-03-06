/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:23:19 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/19 17:11:52 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "libft.h"

# define BUFSIZE 8192

# define BUILT_IN_NUMBER 7

int				ft_cd(int ac, char **av, t_list **envlist);
int				ft_echo(int ac, char **av, t_list **envlist);
int				ft_pwd(void);
int				ft_exit(int ac, char **av, t_list **envlist);
int				ft_env(int ac, char **av, t_list **envlist);
int				ft_unset(int ac, char **av, t_list **envlist);
int				ft_export(int ac, char **av, t_list **envlist);
int				check_export_arg(char *word);

typedef struct	s_built_in {
	char		*name;
	int			(*handler)();
}				t_built_in;

t_built_in		g_built_in[BUILT_IN_NUMBER];

#endif
