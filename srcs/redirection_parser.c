/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:45:37 by darbib            #+#    #+#             */
/*   Updated: 2021/01/17 19:57:34 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		store_redirection(t_list **redirections, t_io_redirect *redirection)
{
	t_io_redirect	*redirection_content;
	t_list			*redirection_node;
	
	redirection_content = (t_io_redirect *)ft_calloc(1, sizeof(t_io_redirect));
	if (!redirection_content)
		return (0);
	*redirection_content = *redirection;
	redirection_node = ft_lstnew(redirection_content);
	if (!redirection_node)
		return (0);
	if (!*redirections)
		*redirections = redirection_node;
	else
		ft_lstadd_back(redirections, redirection_node);
	return (1);
}

enum e_redirect_type	get_redirection_type(t_token token)
{
	if (token.type == DGREAT_TOKEN)
		return (oa_redirect);
	if (token.type == GREAT_TOKEN)
		return (oc_redirect);
	return (i_redirect);
}

void	parse_filename(t_llparser *parser, t_io_redirect *redirection)
{
	t_token current_token;

	current_token = read_token(parser);
	if (current_token.type == WORD_TOKEN)
	{
		parser->state = found;
		redirection->filename = extract_word(current_token);
		//if (!redirection->filename)
		//	sys_error;
		eat(parser);
	}
	else
		parser->state = error;
}

void	parse_io_file(t_llparser *parser, t_io_redirect *redirection)
{
	t_token current_token;
	
	current_token = read_token(parser);
	if (isredirection_op(&current_token))
	{
		eat(parser);
		parse_filename(parser, redirection);
		redirection->type = get_redirection_type(current_token);
	}
}

void	parse_io_redirect(t_llparser *parser)
{
	t_io_redirect	redirection;
	t_token			current_token;
	int				store_success;

	current_token = read_token(parser);
	redirection.io_number = -1; 
	if (current_token.type == IONUMBER_TOKEN)
	{
		eat(parser);
		redirection.io_number = ft_atoi(current_token.value);
	}
	parser->state = base;
	parse_io_file(parser, &redirection);
	store_success = 1;
	if (parser->state == found)
		store_success = store_redirection(&parser->redirections, &redirection);
	//if (!store_success)	
	//	sys_error
}
