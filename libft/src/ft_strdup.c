/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:26:12 by darbib            #+#    #+#             */
/*   Updated: 2019/11/05 11:14:13 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s_out;

	len = ft_strlen(s1);
	if (!(s_out = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_memcpy((void *)s_out, (const void *)s1, len);
	s_out[len] = 0;
	return (s_out);
}
