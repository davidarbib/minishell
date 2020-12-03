/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:17:14 by darbib            #+#    #+#             */
/*   Updated: 2019/11/14 18:28:52 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		free_words(char **w)
{
	while (*w)
		free(*w++);
	free(*w);
	free(w);
}

static size_t	count_w(char const *s, char c)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	if (!*s)
		return (nb);
	while (s[i])
	{
		if (s[i] == c && (s[i + 1] != c && s[i + 1]))
			nb++;
		i++;
	}
	nb++;
	return (nb);
}

static char		**divide(char const *s, char c, size_t nb)
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
		while (s[j] && s[j] != c)
			j++;
		if (!(words[i++] = ft_substr(s, 0, j)))
		{
			free_words(words);
			return (NULL);
		}
		while (s[j] && s[j] == c)
			j++;
		s += j;
	}
	return (words);
}

char			**ft_split(char const *s, char c)
{
	char	**words;
	size_t	i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	s += i;
	if (!(words = divide(s, c, count_w(s, c))))
		return (NULL);
	return (words);
}
