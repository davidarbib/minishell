/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:38:40 by darbib            #+#    #+#             */
/*   Updated: 2021/02/17 15:12:03 by darbib           ###   ########.fr       */
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
t_lexer		analyse_command(char *command, t_lexer *lexer, t_fsm *fsm)
{
	int		i;

	i = -1;
	while (command[++i])
	{
		if (handle_notquoted_char(lexer, fsm, command[i]))
			continue;
		handle_quote_cancel_char(fsm, command[i]);
		if (!add_char_to_fsm_buffer(fsm, command[i]))
		{
			lexer->state = KO_STATE;
			return (*lexer);
		}
		fsm->current_token.type = WORD_TOKEN;
		if (fsm->state == ESCAPE_STATE)
			fsm->state = NORMAL_STATE;
	}
	if (fsm->state >= QUOTE_STATE && fsm->state <= ESCAPE_STATE)
		lexer->state = MULTILINE_STATE;
	if (!delimit_token(lexer, fsm))
		lexer->state = KO_STATE;
	return (*lexer);
}

t_lexer		analyse_command_wrapper(char *command)
{
	t_lexer		lexer;
	t_fsm		fsm;

	init_lexer_fsm(&lexer, &fsm);
	analyse_command(command, &lexer, &fsm);
	exit_lexing(&lexer, &fsm);
	return (lexer);
}

void	delete_token(void *content)
{
	free(content);
}

/*
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
