/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 22:56:09 by darbib            #+#    #+#             */
/*   Updated: 2021/01/17 18:08:31 by darbib           ###   ########.fr       */
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

#include "assignment.h"
void	parse_assignment(t_llparser *parser)
{
	t_token token;

	token = read_token(parser);
	detect_assignment(&token);
	parser->state = base;
	if (token.type == ASSIGNMENT_TOKEN)
	{
		parser->state = found;
		eat(parser);
	}
}

#include <stdio.h>
void	parse_prefix(t_llparser *parser)
{
	printf("parser->state : %d\n", parser->state);
	parse_assignment(parser);
	if (parser->state != found)
		parse_io_redirect(parser);
	if (parser->state == found)
		parse_prefix(parser);
}
