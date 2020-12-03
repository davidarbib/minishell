/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:30:45 by darbib            #+#    #+#             */
/*   Updated: 2019/11/14 18:36:50 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *s_out;

	s_out = (char *)s + ft_strlen(s);
	while (s_out != s && *s_out != (unsigned char)c)
		s_out--;
	if (*s_out == (unsigned char)c)
		return (s_out);
	return (NULL);
}
