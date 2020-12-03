/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:46:56 by darbib            #+#    #+#             */
/*   Updated: 2020/08/09 18:30:52 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"

int		read_and_join(char **line, int fd)
{
	int		same_char;
	int		rd_result;
	char	buf[1];
	char	tmp;

	same_char = 0;
	tmp = 0;
	while ((rd_result = read(fd, buf, 1)) > 0)
	{
		if (*buf == '\n')
			break ;
		if (tmp == *buf)
			same_char++;
		if (same_char > 1000)
			return (-1);
		else
			same_char = 0;
		if (!(*line = ft_strjoinfree(*line, buf, 1)))
			return (-1);
		tmp = *buf;
	}
	if (rd_result < 1)
		return (rd_result);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int		result;

	if (fd < 0 || !line)
		return (-1);
	if (!(*line = ft_calloc(1, sizeof(char))))
		return (-1);
	result = read_and_join(line, fd);
	if (result < 1)
		return (result);
	return (1);
}
