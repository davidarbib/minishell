/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:24:55 by darbib            #+#    #+#             */
/*   Updated: 2021/01/25 14:20:08 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
int	store_args(t_list **args, char *arg)
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

int	parse_word(t_llparser *parser)
{
	char	*arg;
	int		success;
	t_token	current_token;

	current_token = read_token(parser);
	if (current_token.type == WORD_TOKEN)
	{
		arg = extract_word(current_token);
		//printf("current arg : %s\n", arg);
		success = store_args(&parser->current_command->args, arg);
		//if (!success)
		//	sys_error();
		eat(parser);
		return (1);
	}
	return (0);
}

int	parse_cmd_name(t_llparser *parser)
{
	return (parse_word(parser));
}

int	parse_cmd_word(t_llparser *parser)
{
	return (parse_word(parser));
}
