/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:23:19 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/10 18:56:11 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "libft.h"

# define BUFSIZE 8192

int		ft_cd(int ac, char **av, t_list **envlist);
void	ft_echo(int ac, char **av, t_list **env);
int		ft_pwd(void);

#endif
