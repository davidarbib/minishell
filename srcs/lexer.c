/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:38:40 by darbib            #+#    #+#             */
/*   Updated: 2021/01/27 13:23:23 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>
#include "lexer.h"
#include "libft.h"

t_token		const g_seeked_tokens[TOKENS_NB] = 
{
	{GREAT_TOKEN, ">", 1},
	{DGREAT_TOKEN, ">>", 2},
	{LESS_TOKEN, "<", 1},
	{PIPE_TOKEN, "|", 1},
	{SCOLON_TOKEN, ";", 1},
	{NEWLINE_TOKEN, "\n", 1}
};

/*
** handler return 1 if current_char was handled, 0 if not
*/
int			handle_notquoted_char(t_lexer *lexer, t_fsm *fsm, char current_char)
{
	if (fsm->state != NORMAL_STATE)
		return (0);	
	if (is_operator(&fsm->current_token))
	{
		if (check_operator_completion(lexer, fsm, current_char))
			return (1);
	}
	if (check_quoting_char(fsm, current_char))
		return (1);
	if (check_substitution_mark(fsm, current_char))
		return (1);
	if (check_new_op(lexer, fsm, current_char))
		return (1);
	if (check_blank(lexer, fsm, current_char))
		return (1);
	return (0);
}

void		handle_quote_cancel_char(t_fsm *fsm, char current_char)
{
	if (fsm->state == QUOTE_STATE && current_char == '\'')
		fsm->state = NORMAL_STATE;
	if (fsm->state == DQUOTE_STATE && current_char == '\"')
		fsm->state = NORMAL_STATE;
}

/*
** Token recognition rule 9 is ignored on purpose here ('#' handling)
*/
t_lexer		analyse_command(char *command)
{
	t_lexer		lexer;
	t_fsm		fsm;
	int			i;

	init_lexer_fsm(&lexer, &fsm);
	i = -1;
	while (command[++i])
	{
		if (handle_notquoted_char(&lexer, &fsm, command[i]))
			continue;
		handle_quote_cancel_char(&fsm, command[i]);
		fsm.buf[fsm.count++] = command[i];
		fsm.current_token.type = WORD_TOKEN;
		if (fsm.state == ESCAPE_STATE)
			fsm.state = NORMAL_STATE;
	}
	if (fsm.state != NORMAL_STATE)
		printf("multiline requested\n");
	if (fsm.current_token.type != DUMMY_TOKEN)
		delimit_token(&lexer, &fsm);
	return (lexer);
}

void	delete_token(void *content)
{
	free(content);
}

#include "parser.h"
int main()
{	
	//-----parsing tests with shell list-----
	//
	printf("-----------------------------\n");
	//char *input = "echo \'ohoh\'";
	//char *input = " a==42 b=67 c=\"4\"45> out 3> less > true >> haha < ok echo test";
	//char *input = "echo \"echo 4\"test";
	//char *input = "echo test | a=4 cat cc ; ls -l | cat -e";
	char *input = "echo test | a=4 cat cc ; ls -l || cat -e";
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
	parser.shell_list = NULL;
	parse_shell_list(&parser, &parser.shell_list);
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
}
*/
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
}
*/
/*
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
