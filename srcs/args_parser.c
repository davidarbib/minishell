/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:24:55 by darbib            #+#    #+#             */
/*   Updated: 2021/01/19 15:32:13 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
int		store_args(t_list **args, char *arg)
{
	t_list			*args_node;
	
	args_node = ft_lstnew(arg);
	if (!args_node)
		return (0);
	if (!*args)
		*args = args_node;
	else
		ft_lstadd_back(args, args_node);
	return (1);
}
