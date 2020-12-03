/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_blank.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:07:59 by darbib            #+#    #+#             */
/*   Updated: 2020/03/04 16:25:52 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void		free_words(char **w)
{
	while (*w)
		free(*w++);
	free(*w);
	free(w);
}

static size_t	count_w(char const *s)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	if (!*s)
		return (nb);
	while (s[i])
	{
		if (ft_isblank(s[i]) && (!ft_isblank(s[i + 1]) && s[i + 1]))
			nb++;
		i++;
	}
	nb++;
	return (nb);
}

static char		**divide(char const *s, size_t nb)
{
	char	**words;
	size_t	i;
	size_t	j;

	if (!(words = ft_calloc(nb + 1, sizeof(char *))))
		return (NULL);
	words[nb] = NULL;
	i = 0;
	while (i < nb)
	{
		j = 0;
		while (s[j] && !ft_isblank(s[j]))
			j++;
		if (!(words[i++] = ft_substr(s, 0, j)))
		{
			free_words(words);
			return (NULL);
		}
		while (s[j] && ft_isblank(s[j]))
			j++;
		s += j;
	}
	return (words);
}

char			**ft_split_blank(char const *s)
{
	char	**words;
	size_t	i;

	i = 0;
	while (s[i] && ft_isblank(s[i]))
		i++;
	s += i;
	if (!(words = divide(s, count_w(s))))
		return (NULL);
	return (words);
}
