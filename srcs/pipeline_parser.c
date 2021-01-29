/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:21:02 by darbib            #+#    #+#             */
/*   Updated: 2021/01/29 19:57:01 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "obj_destructor.h"

int	parse_pipe(t_llparser *parser)
{
	if (read_token(parser).type == PIPE_TOKEN)
	{
		eat(parser);
		return (1);
	}
	return (0);
}

int	parse_pipeline(t_llparser *parser, t_pipeline **current_pipeline)
{
	if (!parse_simple_command(parser, current_pipeline))
		return (0);
	parser->state = found;
	if (parse_pipe(parser))
	{
		parser->state = base;
		parse_pipeline(parser, current_pipeline);
		//if (!parse_pipeline(parser, current_pipeline))
		if (parser->state == base)
			parser->state = multiline;
	}
	return (0);
}
