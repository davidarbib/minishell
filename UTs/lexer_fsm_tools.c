/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fsm_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 23:52:50 by darbib            #+#    #+#             */
/*   Updated: 2021/02/17 23:53:04 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
int main()
{
	t_lexer lexer;
	t_fsm fsm;
	t_token token;

	init_lexer_fsm(&lexer, &fsm);
	token.type = WORD_TOKEN;
	token.value = strdup("ok");
	token.size = 2;
	add_token(&lexer, token, &fsm);
	token.type = PIPE_TOKEN;
	token.value = strdup("|");
	token.size = 1;
	add_token(&lexer, token, &fsm);
	for (int i = 0; i < lexer.count; i++)
	{
		printf("token : %s\n", lexer.tokens[i].value);
		printf("token type: %u\n", lexer.tokens[i].type);
	}
	add_char_to_fsm_buffer(&fsm, 'a', &lexer);
	printf("fsm.buf : --%s--\n", fsm.buf);
	add_char_to_fsm_buffer(&fsm, 'b', &lexer);
	printf("fsm.buf : --%s--\n", fsm.buf);
	add_char_to_fsm_buffer(&fsm, 'c', &lexer);
	printf("fsm.buf : --%s--\n", fsm.buf);
}
*/
