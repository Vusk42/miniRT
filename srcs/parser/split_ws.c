/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ws.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:51:09 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/29 12:35:59 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

static int	ft_count_words(const char *s)
{
	int	count;
	int	in;

	count = 0;
	in = 0;
	while (*s != '\0')
	{
		if (ft_isspace(*s) == 0 && in == 0)
		{
			in = 1;
			count++;
		}
		else if (ft_isspace(*s) != 0)
			in = 0;
		s++;
	}
	return (count);
}

static int	ft_word_len(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0' && ft_isspace(s[len]) == 0)
		len++;
	return (len);
}

static char	*ft_word_dup(const char *s, int len)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_fill(char **tab, const char *s)
{
	int	len;
	int	i;

	i = 0;
	while (*s != '\0')
	{
		while (ft_isspace(*s) != 0)
			s++;
		if (*s != '\0')
		{
			len = ft_word_len(s);
			tab[i] = ft_word_dup(s, len);
			if (tab[i] == NULL)
				return (NULL);
			i++;
			s += len;
		}
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_split_ws(const char *s)
{
	char	**tab;
	char	**res;

	tab = malloc(sizeof(char *) * (ft_count_words(s) + 1));
	if (!tab)
		return (NULL);
	res = ft_fill(tab, s);
	if (!res)
		ft_freeptr((void **)tab);
	return (res);
}
