/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 22:16:35 by darbib            #+#    #+#             */
/*   Updated: 2021/01/27 11:43:57 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		store_pipeline(t_list **shell_list, t_pipeline *pipeline)
{
	t_pipeline		*shell_list_content;
	t_shell_list	*shell_list_node;
	
	shell_list_content = (t_pipeline *)ft_calloc(1, sizeof(t_pipeline));
	if (!shell_list_content)
		return (0);
	*shell_list_content = *pipeline;
	shell_list_node = ft_lstnew(shell_list_content);
	if (!shell_list_node)
		return (0);
	if (!*shell_list)
		*shell_list = shell_list_node;
	else
		ft_lstadd_back(shell_list, shell_list_node);
	return (1);
}

int	parse_sep(t_llparser *parser)
{
	if (read_token(parser).type == SCOLON_TOKEN)
	{
		eat(parser);
		return (1);
	}
	return (0);
}

int	parse_shell_list(t_llparser *parser, t_shell_list **shell_list)
{
	t_pipeline	*current_pipeline;
	int			success;

	current_pipeline = NULL;
	parser->state = base;
	parse_pipeline(parser, &current_pipeline);
	if (parser->state == found)
	{
		success = store_pipeline(shell_list, current_pipeline);
		if (parse_sep(parser))
			return (parse_shell_list(parser, shell_list));
	}
	return (0);
}