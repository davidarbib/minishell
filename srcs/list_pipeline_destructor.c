/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pipeline_destructor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 23:36:33 by darbib            #+#    #+#             */
/*   Updated: 2021/02/17 23:43:05 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "obj_destructor.h"

void	del_pipeline_content(void *content)
{
	t_simple_command	*command;

	command = (t_simple_command *)content;
	destroy_command(command);
	ft_memdel(&content);
}

void	del_shell_list_content(void *content)
{
	t_pipeline	*pipeline;

	pipeline = (t_pipeline *)content;
	destroy_pipeline(&pipeline);
}

void	destroy_pipeline(t_pipeline **pipeline)
{
	ft_dlstclear(pipeline, del_pipeline_content);
}

void	destroy_shell_list(t_shell_list **shell_list)
{
	ft_lstclear(shell_list, del_shell_list_content);
}

void	destroy_command(t_simple_command *command)
{
	ft_lstclear(&command->redirections, del_redir_content);
	ft_lstclear(&command->args, del_arg_content);
	ft_lstclear(&command->assignments, del_assign_content);
}
