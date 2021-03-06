/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 19:22:37 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/21 13:56:53 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "errno.h"
#include <stdlib.h>
#include <unistd.h>

int			do_malloc(char **buf, size_t size)
{
	free(*buf);
	if (!(*buf = malloc(size)))
	{
		perror("pwd");
		return (-1);
	}
	return (0);
}

static void	error(void)
{
	ft_dprintf(2, "pwd: error retrieving current directory: getcwd:"
	" cannot access parent directories: %s\n", strerror(errno));
}

int			ft_pwd(void)
{
	char	*buf;
	size_t	size;

	size = BUFSIZE;
	while (1)
	{
		buf = 0;
		if (do_malloc(&buf, size) == -1)
			return (1);
		if (!(getcwd(buf, size)) && errno != ERANGE)
		{
			error();
			break ;
		}
		if (buf)
		{
			ft_printf("%s\n", buf);
			break ;
		}
		free(buf);
		size *= 100;
	}
	free(buf);
	return (0);
}
