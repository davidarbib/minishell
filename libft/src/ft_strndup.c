/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 22:36:53 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/02/18 22:42:17 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t size)
{
	char	*s_out;

	if (!(s_out = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_memcpy((void *)s_out, (const void *)s1, size);
	s_out[size] = 0;
	return (s_out);
}
