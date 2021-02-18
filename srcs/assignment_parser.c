/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 09:33:37 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 15:06:16 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assignment.h"
#include "obj_destructor.h"
#include "parser.h"

int			store_assignment(t_list **assignments, t_assignment *assignment)
{
	t_assignment	*assignment_content;
	t_list			*assignment_node;

	assignment_content = (t_assignment *)ft_calloc(1, sizeof(t_assignment));
	if (!assignment_content)
		return (0);
	*assignment_content = *assignment;
	assignment_node = ft_lstnew(assignment_content);
	if (!assignment_node)
	{
		ft_memdel((void **)&assignment_content);
		return (0);
	}
	if (!*assignments)
		*assignments = assignment_node;
	else
		ft_lstadd_back(assignments, assignment_node);
	return (1);
}

int			split_assignment(t_token token, t_assignment *assignment)
{
	if (!ft_split_dict(token.value, '=', &assignment->key, &assignment->value))
		return (0);
	return (1);
}

static void	init_parse_assignment(t_assignment *assignment)
{
	assignment.key = NULL;
	assignment.value = NULL;
}

int			parse_assignment(t_llparser *parser)
{
	t_token			token;
	t_assignment	assignment;

	init_parse_assignment(parser, &assignment);
	token = read_token(parser);
	detect_assignment(&token);
	if (token.type == ASSIGNMENT_TOKEN)
	{
		eat(parser);
		if (!split_assignment(token, &assignment))
		{
			destroy_assignment(&assignment);
			parser->state = sys_error;
			return (0);
		}
		if (!store_assignment(&parser->current_command->assignments,
								&assignment))
		{
			destroy_assignment(&assignment);
			parser->state = sys_error;
			return (0);
		}
		return (1);
	}
	return (0);
}
