/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 22:51:12 by darbib            #+#    #+#             */
/*   Updated: 2021/02/03 19:15:56 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CD_H
# define FT_CD_H

# include "assignment.h"

# define BUFSIZE 8192

int		ft_cd(int ac, char **av, t_list **envlist);
#endif
