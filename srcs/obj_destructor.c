/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_destructor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:52:10 by darbib            #+#    #+#             */
/*   Updated: 2021/01/28 16:47:14 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assignment.h"
#include "libft.h"
#include "parser.h"
#include "obj_destructor.h"

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

void	del_pipeline_content(void *content)
{
	t_simple_command *command;
	
	command = (t_simple_command *)content;
	destroy_command(command);
	ft_memdel(&content);
}

void	del_shell_list_content(void *content)
{
	t_pipeline	*pipeline;
	
	pipeline = (t_pipeline *)content;
	destroy_pipeline(&pipeline);
	//ft_memdel(&content);
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
