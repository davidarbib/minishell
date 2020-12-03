/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:04:53 by darbib            #+#    #+#             */
/*   Updated: 2019/11/19 14:31:50 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
