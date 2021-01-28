/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:13:58 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/01/28 14:47:58 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "lexer.h"
# include "parser.h"
# include <stdio.h>

/*
** g_env is a t_list of t_assignment
*/

t_list	*g_env;

t_list	*lookup(char *key, t_list *assignments);

/*
** parser_interface.c
*/

int		parse(t_lexer *lexer, t_llparser *parser, char *line);
void	initialize_parser(t_llparser *parser, t_lexer *lexer);

#endif
