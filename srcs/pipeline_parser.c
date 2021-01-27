/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:21:02 by darbib            #+#    #+#             */
/*   Updated: 2021/01/25 14:21:30 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	{
		parser->state = error;
		return (0);
	}
	if (parse_pipe(parser))
		return (parse_pipeline(parser, current_pipeline));
	return (0);
}
