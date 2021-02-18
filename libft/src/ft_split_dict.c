/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_dict.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 12:29:54 by darbib            #+#    #+#             */
/*   Updated: 2021/02/18 13:27:32 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_split_dict(const char *s, char c, char **key, char **value)
{
	char	*equal_ptr;
	int		key_len;
	int		value_len;

	equal_ptr = ft_strchr(s, c);
	key_len = equal_ptr - s;
	*key = ft_substr(s, 0, key_len);
	if (!*key)
		return (0);
	value_len = ft_strlen(s) - (key_len + 1);
	*value = ft_substr(equal_ptr + 1, 0, value_len);
	if (!*value)
		return (0);
	return (1);
}
