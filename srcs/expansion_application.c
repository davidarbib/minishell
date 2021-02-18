/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_application.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 20:03:01 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 21:07:29 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_quote_removal.h"
#include "parser.h"

int		expand_simple_command(t_simple_command *command)
{
	return (!expand_args_redirections(command->args, command->redirections));
}

int		expand_pipeline(t_pipeline *pipeline)
{
	int	error;

	if (!pipeline)
		return (0);
	error = expand_simple_command((t_simple_command *)pipeline->content);
	if (error)
		return (error);
	return (expand_pipeline(pipeline->next));
}
