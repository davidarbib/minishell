/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_destructor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:52:10 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 12:29:11 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assignment.h"
#include "libft.h"
#include "parser.h"

void	destroy_assignment(t_assignment *assignment)
{
	ft_memdel((void **)&assignment->key);
	ft_memdel((void **)&assignment->value);
}

void	del_redir_content(void *content)
{
	t_io_redirect	*redir;

	redir = (t_io_redirect *)content;
	ft_memdel((void **)&redir->filename);
	ft_memdel(&content);
}

void	del_assign_content(void *content)
{
	t_assignment	*assignment;

	assignment = (t_assignment *)content;
	destroy_assignment(assignment);
	ft_memdel(&content);
}

void	del_arg_content(void *content)
{
	ft_memdel(&content);
}
