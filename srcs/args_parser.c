/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:24:55 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 13:29:16 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		store_args(t_list **args, char *arg)
{
	t_list			*args_node;

	args_node = ft_lstnew(arg);
	if (!args_node)
		return (0);
	if (!*args)
		*args = args_node;
	else
		ft_lstadd_back(args, args_node);
	return (1);
}

char	*extract_word(t_token token)
{
	char	*word;

	word = ft_calloc(token.size + 1, sizeof(char));
	if (!word)
		return (NULL);
	ft_memmove(word, token.value, token.size);
	return (word);
}

int		parse_word(t_llparser *parser)
{
	char	*arg;
	int		success;
	t_token	current_token;

	current_token = read_token(parser);
	if (current_token.type == WORD_TOKEN)
	{
		arg = extract_word(current_token);
		if (!arg)
		{
			parser->state = sys_error;
			return (0);
		}
		success = store_args(&parser->current_command->args, arg);
		if (!success)
		{
			parser->state = sys_error;
			ft_memdel((void **)&arg);
			return (0);
		}
		eat(parser);
		return (1);
	}
	return (0);
}

int		parse_cmd_name(t_llparser *parser)
{
	t_token	current_token;

	current_token = read_token(parser);
	detect_assignment(&current_token);
	if (current_token.type != WORD_TOKEN)
		return (0);
	return (parse_word(parser));
}

int		parse_cmd_word(t_llparser *parser)
{
	t_token	current_token;

	current_token = read_token(parser);
	detect_assignment(&current_token);
	if (current_token.type != WORD_TOKEN)
		return (0);
	return (parse_word(parser));
}
