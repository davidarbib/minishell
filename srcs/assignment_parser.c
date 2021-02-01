/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 09:33:37 by darbib            #+#    #+#             */
/*   Updated: 2021/01/27 17:14:57 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assignment.h"
#include "obj_destructor.h"
#include "parser.h"

int		store_assignment(t_list **assignments, t_assignment *assignment)
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int		split_assignment(t_token token, t_assignment *assignment)
{
	char	*equal_ptr;
	int		key_len;
	int		value_len;
	
	equal_ptr = ft_strchr(token.value, '=');
	key_len = equal_ptr - token.value;
	assignment->key = ft_substr(token.value, 0, key_len);
	if (!assignment->key)
		return (0);
	value_len = token.size - (key_len + 1);
	assignment->value = ft_substr(equal_ptr + 1, 0, value_len);
	if (!assignment->value)
		return (0);
	return (1);	
}

/*
int main()
{
	t_token token;
	t_assignment assignment;

	token.type = 0;
	token.value = "az=45";
	token.size = strlen(token.value);
	assignment.key = NULL;
	assignment.value = NULL;
	split_assignment(token, &assignment);
	printf("key : %s\n", assignment.key);
	printf("value : %s\n", assignment.value);
}
*/

int		parse_assignment(t_llparser *parser)
{
	t_token			token;
	t_assignment	assignment;

	token = read_token(parser);
	assignment.key = NULL;
	assignment.value = NULL;
	if (token.type == ASSIGNMENT_TOKEN)
	{
		eat(parser);
		if (!split_assignment(token, &assignment))
		{
			destroy_assignment(&assignment);
			parser->state = sys_error;
			return (0);
		}
		if (!store_assignment(&parser->current_command->assignments, &assignment))
		{
			destroy_assignment(&assignment);
			parser->state = sys_error;
			return (0);
		}
		return (1);
	}
	return (0);
}
