/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 15:39:41 by darbib            #+#    #+#             */
/*   Updated: 2020/08/09 18:27:41 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdelchar(char *s, char c)
{
	char	*s_out;
	int		i;

	if (!(s_out = ft_calloc(ft_strlen(s) + 1, sizeof(char))))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
			s_out[i++] = *s;
		s++;
	}
	return (s_out);
}
