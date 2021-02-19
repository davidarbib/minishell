/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:51:31 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/19 13:43:17 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signal)
{
	t_list	*tmp;

	tmp = g_all_childs;
	if (!tmp)
	{
		if (signal != SIGINT)
			write(2, FONT_BOLDBLUE "\nminishell-1.0$ " FONT_RESET, 27);
		return ;
	}
	while (tmp)
	{
		kill(*(int*)tmp->content, signal);
		tmp = tmp->next;
	}
	if (signal != SIGINT)
		printf("Quit: %d", signal);
	printf("\n");
}
