/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_destructor.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:55:35 by darbib            #+#    #+#             */
/*   Updated: 2021/01/28 20:43:36 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_DESTRUCTOR_H
# define OBJ_DESTRUCTOR_H

# include "parser.h"

void	destroy_assignment(t_assignment *assignment);
void	destroy_command(t_simple_command *command);
void	destroy_shell_list(t_shell_list **shell_list);
void	destroy_pipeline(t_pipeline **pipeline);
void	destroy_tokens(t_token **tokens, size_t size);
void	del_pipeline_content(void *content);
void	del_arg_content(void *content);
void	del_assign_content(void *content);
void	del_redir_content(void *content);
#endif
