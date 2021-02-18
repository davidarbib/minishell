/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 11:18:17 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 11:18:21 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
int main()
{
	//-----tests for match_operator
	char *op = "|";
	t_token token = match_operator(op);
	printf("type of %s : %d\n", op, token.type);
	printf("%d\n", DGREAT_TOKEN);
	
	//-----tests for is_operator
	token.type = GREAT_TOKEN;
	printf("great is an operator : %d\n", is_operator(&token));
	token.type = DUMMY_TOKEN;
	printf("dummy is an operator : %d\n", is_operator(&token));
	token.type = PIPE_TOKEN;
	printf("pipe is an operator : %d\n", is_operator(&token));
	token.type = TEXT_TOKEN;
	printf("text is an operator : %d\n", is_operator(&token));

	//-----tests for delimit_token
	printf("---------------------\n");
#define LEXERSIZE 3
	t_lexer lexer;
	t_fsm fsm;

	lexer.tokens = malloc(sizeof(t_token) * LEXERSIZE);
	lexer.count = 0;
	lexer.size = LEXERSIZE;
	fsm.state = NORMAL_STATE;
	fsm.current_token.type = SCOLON_TOKEN;
	memcpy(fsm.buf, ";", 1);
	fsm.count = 1;
	fsm.size = 1024;
	delimit_token(&lexer, &fsm);
	
	fsm.current_token.type = PIPE_TOKEN;
	memcpy(fsm.buf, "|", 1);
	fsm.count = 1;
	delimit_token(&lexer, &fsm);

	fsm.current_token.type = DGREAT_TOKEN;
	memcpy(fsm.buf, ">>", 2);
	fsm.count = 1;
	delimit_token(&lexer, &fsm);
	for (size_t i = 0; i < lexer.size; i++)
	{
		printf("token : %s\n", lexer.tokens[i].value);
		printf("token type: %u\n", lexer.tokens[i].type);
	}
}
*/
