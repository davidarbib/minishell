
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 22:02:25 by darbib            #+#    #+#             */
/*   Updated: 2020/12/05 20:00:44 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

void	*ft_realloc(void *area, size_t in_bytes_n, size_t out_bytes_n)
{
	void	*p_out;
	if (in_bytes_n > out_bytes_n)
		in_bytes_n = out_bytes_n;
	if (!(p_out = ft_calloc(out_bytes_n, sizeof(unsigned char))))
		return (NULL);
	ft_memcpy(p_out, (const void *)area, in_bytes_n);
	free(area);
	return (p_out);
}
