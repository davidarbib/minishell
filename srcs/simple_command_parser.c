/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_parser.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:35:27 by darbib            #+#    #+#             */
/*   Updated: 2021/01/27 11:43:42 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		store_simple_command(t_pipeline **pipeline, t_simple_command *command)
{
	t_simple_command	*pipeline_content;
	t_pipeline			*pipeline_node;
	
	pipeline_content = (t_simple_command *)ft_calloc(1, sizeof(t_simple_command));
	if (!pipeline_content)
		return (0);
	*pipeline_content = *command;
	pipeline_node = ft_dlstnew(pipeline_content);
	if (!pipeline_node)
		return (0);
	if (!*pipeline)
		*pipeline = pipeline_node;
	else
		ft_dlstadd_back(pipeline, pipeline_node);
	return (1);
}

void	init_simple_command(t_simple_command *command)
{
	command->redirections = NULL;
	command->assignments = NULL;
	command->args = NULL;
}

int	parse_prefix(t_llparser *parser)
{
	int success;
	//printf("parser->state : %d\n", parser->state);
	success = parse_assignment(parser);
	if (!success)
		success = parse_io_redirect(parser);
	if (success)
	{
		parser->state = found;
		return (parse_prefix(parser));
	}
	return (0);
}

int	parse_suffix(t_llparser *parser)
{
	int success;

	parser->state = base;
	success = parse_word(parser);
	if (!success)
		parse_io_redirect(parser);
	if (success)
		return (parse_suffix(parser));
	return (0);
}

int		parse_simple_command(t_llparser *parser, t_pipeline **current_pipeline)
{
	t_simple_command	command;
	int					success;

	init_simple_command(&command);
	parser->state = base;
	parser->current_command = &command;
	if (parse_cmd_name(parser))
		parse_suffix(parser);
	else
	{
		if (!parse_prefix(parser) && parser->state == base)
			return (0);
		if (parse_cmd_word(parser))
			parse_suffix(parser);
	}
	success = store_simple_command(current_pipeline, &command);
	//if (!success)
	//	sys_error();
	return (1);
}
