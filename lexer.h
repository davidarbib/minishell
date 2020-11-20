/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:38:45 by darbib            #+#    #+#             */
/*   Updated: 2020/11/20 16:05:26 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stdlib.h>

enum			e_token
{
	white_token,
	word_token,
	pipe_token,
	separator_token,
	redir_token
};

typedef struct	s_token
{
	enum e_token	type;
	const char 		*value;
	size_t			size;
}				t_token;

typedef struct	s_lexer
{
	t_token			*tokens;
	size_t			size;
}				t_lexer;

t_token		static const g_remarkable_tokens[1] = 
{
	{redir_token, ">>", 2}
};
#endif
