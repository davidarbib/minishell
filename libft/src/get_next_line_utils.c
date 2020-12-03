/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:21:28 by darbib            #+#    #+#             */
/*   Updated: 2020/02/24 16:19:07 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_dst;

	len_dst = ft_strlen(dst);
	if (dstsize && dstsize > len_dst)
	{
		dst += len_dst;
		i = 0;
		while (src[i] && i < dstsize - len_dst - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
		return (len_dst + ft_strlen(src));
	}
	return (ft_strlen(src) + dstsize);
}

char	*ft_strjoinfree(char const *s1, char const *s2, char clear)
{
	char	*s_out;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!(s_out = ft_calloc(len_s1 + len_s2 + 1, sizeof(char))))
		return (NULL);
	if (len_s1 + 1)
	{
		i = 0;
		while (s1[i] && i < len_s1)
		{
			s_out[i] = s1[i];
			i++;
		}
		s_out[i] = 0;
	}
	ft_strlcat(s_out, s2, len_s1 + len_s2 + 1);
	if (clear == 1 || clear == 3)
		free((void *)s1);
	if (clear == 2 || clear == 3)
		free((void *)s2);
	return (s_out);
}

char	*ft_strdupfree(const char *s1, char clear)
{
	size_t	len;
	size_t	i;
	char	*s_out;

	len = ft_strlen(s1);
	if (!(s_out = ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		((unsigned char *)s_out)[i] = ((unsigned char *)s1)[i];
		i++;
	}
	s_out[len] = 0;
	if (clear)
		free((void *)s1);
	return (s_out);
}
