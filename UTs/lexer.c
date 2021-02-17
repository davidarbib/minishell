/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:08:44 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 00:09:12 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
void	delete_token(void *content)
{
	free(content);
}

#include "parser.h"
#include "obj_destructor.h"

int main()
{	
	//-----tests for analyse_command
	printf("-----------------------------\n");
	char *input = "cat 35> || cat";
	t_lexer lexer7 = analyse_command(input);
	int i = 0;
	while (i < lexer7.count)
	{
		printf("token : %s\n", lexer7.tokens[i].value);
		printf("token type: %u\n", lexer7.tokens[i].type);
		i++;
	}
	printf("-----------------------------\n");
	t_dlist *tokens_lst = ft_tabtodlst(lexer7.tokens, lexer7.count, sizeof(t_token));
	t_dlist *token_node = tokens_lst;
	while (token_node)
	{
		t_token *token = (t_token *)token_node->content;
		printf("token : %s\n", token->value);
		printf("token type: %u\n", token->type);
		printf("token next: %p\n", token_node->next);
		token_node = token_node->next;
	} 
	printf("-----------------------------\n");
	token_node = ft_dlstlast(tokens_lst);
	while (token_node)
	{
		t_token *token = (t_token *)token_node->content;
		printf("token : %s\n", token->value);
		printf("token type: %u\n", token->type);
		printf("token prev: %p\n", token_node->prev);
		token_node = token_node->prev;
	}
	free(lexer7.tokens);
	ft_dlstclear(&tokens_lst, delete_token);
	return (0);
}
*/
