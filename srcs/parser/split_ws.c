/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ws.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:51:09 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:01:41 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

/**
 * @brief Count whitespace-separated words in a string.
 * @param s Input string.
 * @return The number of words.
 */
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

/**
 * @brief Length of the leading word (up to the next whitespace).
 * @param s String starting at a word.
 * @return The number of non-whitespace characters at the start of s.
 */
static int	ft_word_len(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0' && ft_isspace(s[len]) == 0)
		len++;
	return (len);
}

/**
 * @brief Duplicate the first `len` characters of a string into a new buffer.
 * @param s Source string.
 * @param len Number of characters to copy.
 * @return A newly allocated, null-terminated copy, or NULL on allocation
 * failure.
 */
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

/**
 * @brief Fill a pre-sized array with the duplicated words of a string.
 * @param tab Destination array (sized for word count + 1).
 * @param s Input string to tokenize.
 * @return `tab` on success, NULL if a word duplication fails.
 */
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

/**
 * @brief Split a string into words on any run of whitespace.
 * @param s Input string.
 * @return A NULL-terminated array of allocated words, or NULL on failure.
 */
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
