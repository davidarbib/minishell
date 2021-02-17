/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 22:56:09 by darbib            #+#    #+#             */
/*   Updated: 2021/02/16 18:59:17 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	eat(t_llparser *parser)
{
	parser->token_idx++;
}

t_token	read_token(t_llparser *parser)
{
	return (parser->tokens[parser->token_idx]);
}

t_token	*ref_token(t_llparser *parser)
{
	return (&parser->tokens[parser->token_idx]);
}

/*
int main()
{	
#include "obj_destructor.h"
#include <stdio.h>
	//-----parsing tests with shell list-----
	//
	printf("-----------------------------\n");
	//char *input = "echo \'ohoh\'";
	//char *input = " a==42 b=67 c=\"4\"45> out 3> less > true >> haha < ok echo test";
	//char *input = " a==42 b=67 c=\"4\"45> out 3> less > true >> haha 0< ok echo test";
	//char *input = " a==42 b=67 c=\"4\"45> out 3> less > true >> haha < ok echo test";
	//char *input = "echo \'ohoh\' < lol.txt < prout > lol | cat > toto.txt > robert.txt";
	//char *input = "echo \"echo 4\"test";
	//char *input = "echo test | a=4 cat cc ; ls -l | cat -e";
	//char *input = "echo test | a=4 cat cc ; ls -l || cat -e";
	//char *input = "echo test | a=4 cat cc ; ls -l | cat -e |";
	//char *input = "ls >";
	//char *input = "ls > a.out | cat -e ;";
	//char *input = "ls > a.out";
	//char *input = "ls";
	//char *input = "ls | cat | echo";
	//char *input = "ls | cat | echo ; oxo";
	//char *input = "echo a\"$HOME\"";
	//char *input = "a=4 export b=3";
	//char *input = "\"a=4\" export b=3";
	//char *input = "a=\"4\" export b=2";
	//char *input = "\"a=4\" export b=2";
	//char *input = "\"a\"=4 export b=2";
	t_lexer lexer = analyse_command(input);
	int i = 0;
	while (i < lexer.count)
	{
		printf("token : %s\n", lexer.tokens[i].value);
		printf("token type: %u\n", lexer.tokens[i].type);
		i++;
	}
	detect_ionumber(&lexer);
	//detect_assignments(&lexer);
	t_llparser parser;
	parser.tokens = lexer.tokens;
	parser.token_idx = 0;
	parser.state = base;
	parser.shell_list = NULL;
	//t_pipeline *current_pipeline = NULL;
	int ret = parse_shell_list(&parser, &parser.shell_list);
	//int ret = parse_pipeline(&parser, &current_pipeline);
	printf("parse return : %d\n", ret);
	printf("parser state : %d\n", parser.state);
	ret = 1;

	if (!ret)
	{
		//destroy_pipeline(&current_pipeline);
		destroy_shell_list(&parser.shell_list);
		destroy_tokens(&parser.tokens, lexer.count);
		//while (1)
		//	system("Leaks");
		return (1);
	}
	t_shell_list *node_shell_list = parser.shell_list;
	while (node_shell_list)
	{
		printf("#################current pipeline################\n");
		t_pipeline *node_pipeline = node_shell_list->content;
		while (node_pipeline)
		{
			printf("-----------------current simple command-------------------\n");
			t_simple_command *command = (t_simple_command *)node_pipeline->content;
			t_list *node = command->redirections;
			while (node)
			{
				t_io_redirect *redirection = (t_io_redirect *)node->content;
				printf("redir.ionumber : %d\n", redirection->io_number);
				printf("redir.filename : %s\n", redirection->filename);
				printf("redir.type : %d\n", redirection->type);
				node = node->next;
			}
			printf("------------------------------------\n");
			t_list *node2 = command->assignments;
			while (node2)
			{
				t_assignment *assignment = (t_assignment *)node2->content;
				printf("key : %s\n", assignment->key);
				printf("value : %s\n", assignment->value);
				node2 = node2->next;
			}
			printf("------------------------------------\n");
			t_list *node3 = command->args;
			int j = 0;
			while (node3)
			{
				char *arg = (char *)node3->content;
				printf("arg[%d] : %s\n", j, arg);
				node3 = node3->next;
				j++;
			}
			node_pipeline = node_pipeline->next;
		}
		node_shell_list = node_shell_list->next;
	}
}
*/
/*
int main()
{	
	//-----parsing tests with pipeline-----
	//
	printf("-----------------------------\n");
	//char *input = "echo \'ohoh\'";
	//char *input = " a==42 b=67 c=\"4\"45> out 3> less > true >> haha < ok echo test";
	//char *input = "echo \"echo 4\"test";
	char *input = "echo test | a=4 cat cc";
	t_lexer lexer = analyse_command(input);
	int i = 0;
	while (i < lexer.count)
	{
		printf("token : %s\n", lexer.tokens[i].value);
		printf("token type: %u\n", lexer.tokens[i].type);
		i++;
	}
	detect_ionumber(&lexer);
	detect_assignments(&lexer);
	t_llparser parser;
	parser.tokens = lexer.tokens;
	parser.token_idx = 0;
	parser.state = base;
	parser.current_pipeline = NULL;
	parse_pipeline(&parser, &parser.current_pipeline);
	printf("------------------------------------\n");
	t_pipeline *node_pipeline = parser.current_pipeline;
	while (node_pipeline)
	{
		printf("-----------------current simple command-------------------\n");
		t_simple_command *command = (t_simple_command *)node_pipeline->content;
		t_list *node = command->redirections;
		while (node)
		{
			t_io_redirect *redirection = (t_io_redirect *)node->content;
			printf("redir.ionumber : %d\n", redirection->io_number);
			printf("redir.filename : %s\n", redirection->filename);
			printf("redir.type : %d\n", redirection->type);
			node = node->next;
		}
		printf("------------------------------------\n");
		t_list *node2 = command->assignments;
		while (node2)
		{
			t_assignment *assignment = (t_assignment *)node2->content;
			printf("key : %s\n", assignment->key);
			printf("value : %s\n", assignment->value);
			node2 = node2->next;
		}
		printf("------------------------------------\n");
		t_list *node3 = command->args;
		int j = 0;
		while (node3)
		{
			char *arg = (char *)node3->content;
			printf("arg[%d] : %s\n", j, arg);
			node3 = node3->next;
			j++;
		}
		node_pipeline = node_pipeline->next;
	}
}*/
/*
int main()
{	
	//-----parsing tests-----
	//
	printf("-----------------------------\n");
	//char *input = "echo \'ohoh\'";
	//char *input = " a==42 b=67 c=\"4\"45> out 3> less > true >> haha < ok echo test";
	char *input = "echo test | cat cc";
	t_lexer lexer = analyse_command(input);
	int i = 0;
	while (i < lexer.count)
	{
		printf("token : %s\n", lexer.tokens[i].value);
		printf("token type: %u\n", lexer.tokens[i].type);
		i++;
	}
	detect_ionumber(&lexer);
	detect_assignments(&lexer);
	t_llparser parser;
	parser.tokens = lexer.tokens;
	parser.token_idx = 0;
	parser.state = base;
//	parse_prefix(&parser);
	parse_simple_command(&parser, NULL);
	printf("------------------------------------\n");
	t_list *node = parser.current_command->redirections;
	while (node)
	{
		t_io_redirect *redirection = (t_io_redirect *)node->content;
		printf("redir.ionumber : %d\n", redirection->io_number);
		printf("redir.filename : %s\n", redirection->filename);
		printf("redir.type : %d\n", redirection->type);
		node = node->next;
	}
	printf("------------------------------------\n");
	t_list *node2 = parser.current_command->assignments;
	while (node2)
	{
		t_assignment *assignment = (t_assignment *)node2->content;
		printf("key : %s\n", assignment->key);
		printf("value : %s\n", assignment->value);
		node2 = node2->next;
	}
	printf("------------------------------------\n");
	t_list *node3 = parser.current_command->args;
	int j = 0;
	while (node3)
	{
		char *arg = (char *)node3->content;
		printf("arg[%d] : %s\n", j, arg);
		node3 = node3->next;
		j++;
	}
}*/
