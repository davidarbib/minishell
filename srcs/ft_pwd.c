/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 19:22:37 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/18 22:04:26 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "errno.h"
#include <stdlib.h>
#include <unistd.h>

int		do_malloc(char *buf, size_t size)
{
	if (!(buf = malloc(size)))
	{
		perror("pwd");
		return (-1);
	}
	return (0);
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
		if (do_malloc(buf, size) == -1)
			return (1);
		if (!(ret = getcwd(buf, size)) && errno != ERANGE)
		{
			perror("pwd");
			break ;
		}
		if (ret)
		{
			ft_printf("%s\n", ret);
			break ;
		}
		free(buf);
		size *= 100;
	}
	free(buf);
	return (0);
}
