/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 10:48:17 by darbib            #+#    #+#             */
/*   Updated: 2019/11/14 18:30:59 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	n;
	size_t	i;

	if (!(sub_s = ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	n = ft_strlen(s);
	i = 0;
	while (i < len && start < n)
	{
		sub_s[i] = s[start];
		start++;
		i++;
	}
	sub_s[i] = 0;
	return (sub_s);
}
