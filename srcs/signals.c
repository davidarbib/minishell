/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:51:31 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/20 18:36:59 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signal)
{
	t_list	*tmp;

	tmp = g_all_childs;
	if (!tmp)
	{
		if (signal == SIGINT)
			write(2, "\nminishell-1.0$ ", 16);
		else
			write(1, "\b\b  \b\b", 6);
		g_last_command_result = 130;
		return ;
	}
	while (tmp)
	{
		kill(*(int*)tmp->content, signal);
		tmp = tmp->next;
	}
	if (signal != SIGINT)
		printf("Quit");
	printf("\n");
}
