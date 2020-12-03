/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 21:28:38 by darbib            #+#    #+#             */
/*   Updated: 2019/11/14 18:34:01 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_out;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!(s_out = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1))))
		return (NULL);
	ft_strlcpy(s_out, s1, len_s1 + 1);
	ft_strlcat(s_out, s2, len_s1 + len_s2 + 1);
	return (s_out);
}
