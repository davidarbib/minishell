/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 22:56:09 by darbib            #+#    #+#             */
/*   Updated: 2021/01/20 15:16:35 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*extract_word(t_token token)
{
	char	*word;

	word = ft_calloc(token.size + 1, sizeof(char));
	if (!word)
		return (NULL);
	ft_memmove(word, token.value, token.size);
	return (word);
}

/*
#include <string.h>
#include <stdio.h>
int main()
{
	t_token token;
	
	token.value = strdup("test");
	token.size = strlen(token.value);
	token.type = 0;
	char *word = extract_word(token);
	printf("word : --%s--\n", word);
	printf("word len : --%zu--\n", strlen(word));
	free(word);
	free(token.value);
	return (0);
}
*/

void	eat(t_llparser *parser)
{
	parser->token_idx++;
}

/*
void	accept(t_llparser *parser)
{
}
*/

t_token	read_token(t_llparser *parser)
{
	return (parser->tokens[parser->token_idx]);
}

t_token	*ref_token(t_llparser *parser)
{
	return (&parser->tokens[parser->token_idx]);
}

void	parse_cmd_name(t_llparser *parser)
{
	parser->state = base;
	parse_word(parser);
}

void	parse_cmd_word(t_llparser *parser)
{
	parser->state = base;
	parse_word(parser);
}

#include <stdio.h>
void	parse_prefix(t_llparser *parser)
{
	//printf("parser->state : %d\n", parser->state);
	parse_assignment(parser);
	if (parser->state != found)
		parse_io_redirect(parser);
	if (parser->state == found)
		parse_prefix(parser);
}

void	parse_word(t_llparser *parser)
{
	char	*arg;
	t_token	current_token;

	current_token = read_token(parser);
	if (current_token.type == WORD_TOKEN)
	{
		parser->state = found;
		arg = extract_word(current_token);
		printf("current arg : %s\n", arg);
		store_args(&parser->args, arg);
		eat(parser);
	}
}

void	parse_suffix(t_llparser *parser)
{
	parser->state = base;
	parse_word(parser);
	if (parser->state != found)
		parse_io_redirect(parser);
	if (parser->state == found)
		parse_suffix(parser);
}

void	parse_simple_command(t_llparser *parser)
{
	parse_cmd_name(parser);
	if (parser->state == found)	
	{
		parse_suffix(parser);
		return ;
	}
	parse_prefix(parser);
	parse_cmd_word(parser);
	if (parser->state == found)	
		parse_suffix(parser);
}
