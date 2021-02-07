/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:55:07 by darbib            #+#    #+#             */
/*   Updated: 2021/02/07 14:28:49 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# include "libft.h"

t_list	*to_environ_list(char **environ);
char	**to_environ_array(t_list *environ);
char	*ft_getenv(const char *name, t_list *envlist);
int		ft_setenv(char *key, char *value, t_list **envlistp);
char	*ft_getenv(const char *key, t_list *envlist);
t_list	*lookup(const char *key, t_list *envlist);
char	*lookup_value(const char *key, t_list *envlist);

#endif
