/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:38:40 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 12:27:27 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>
#include "lexer.h"
#include "libft.h"

/*
** handler return 1 if current_char was handled, 0 if not
*/

int		handle_notquoted_char(t_lexer *lexer, t_fsm *fsm, char current_char)
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

void	handle_quote_cancel_char(t_fsm *fsm, char current_char)
{
	if (fsm->state == QUOTE_STATE && current_char == '\'')
		fsm->state = NORMAL_STATE;
	if (fsm->state == DQUOTE_STATE && current_char == '\"')
		fsm->state = NORMAL_STATE;
}

/*
** Token recognition rule 9 is ignored on purpose here ('#' handling)
*/

t_lexer	analyse_command(char *command, t_lexer *lexer, t_fsm *fsm)
{
	int	i;

	i = -1;
	while (command[++i])
	{
		if (handle_notquoted_char(lexer, fsm, command[i]))
			continue ;
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

t_lexer	analyse_command_wrapper(char *command)
{
	t_lexer		lexer;
	t_fsm		fsm;

	init_lexer_fsm(&lexer, &fsm);
	analyse_command(command, &lexer, &fsm);
	destroy_fsm(&fsm);
	return (lexer);
}
