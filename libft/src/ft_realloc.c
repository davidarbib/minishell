/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 22:02:25 by darbib            #+#    #+#             */
/*   Updated: 2021/01/21 14:47:12 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

void	*ft_realloc(void *area, size_t in_bytes_n, size_t out_bytes_n)
{
	void	*p_out;
	size_t	bytes;

	if (in_bytes_n > out_bytes_n)
		bytes = out_bytes_n;
	else
		bytes = in_bytes_n;
	if (!(p_out = ft_calloc(bytes, sizeof(unsigned char))))
		return (NULL);
	ft_memcpy(p_out, (const void *)area, bytes);
	free(area);
	return (p_out);
}
