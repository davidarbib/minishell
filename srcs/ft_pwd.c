/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 19:22:37 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/08 18:42:23 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "errno.h"
#include <stdlib.h>

void	do_malloc(char *buf, size_t size)
{
	if (!(buf = malloc(size)))
	{
		perror("pwd");
		exit(EXIT_FAILURE);
	}
}

int		ft_pwd(void)
{
	char	*buf;
	size_t	size;
	char	*ret;

	size = BUFSIZE;
	buf = 0;
	while (1)
	{
		do_malloc(buf, size);
		ret = getcwd(buf, size);
		if (!ret && errno != ERANGE)
		{
			perror("pwd");
			break ;
		}
		if (ret)
		{
			printf("%s\n", ret);
			break ;
		}
		free(buf);
		size *= 100;
	}
	free(buf);
	exit(EXIT_SUCCESS);
}
