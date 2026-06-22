/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:43:12 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 17:02:41 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/string.h"

static int	ft_nbrword(char const *src, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (src[i])
	{
		if (src[i] == c)
			i++;
		else
		{
			word++;
			while (src[i] != c && src[i])
				i++;
		}
	}
	return (word);
}

static void	*ft_insert(char *dest, char const *src, int index, int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		dest[i] = src[index - n];
		i++;
		n--;
	}
	dest[i] = '\0';
	return (dest);
}

static int	ft_create_split(char **split, char const *src, char c, int line)
{
	int	i;
	int	count_line;
	int	len;

	i = 0;
	count_line = 0;
	while (count_line < line)
	{
		len = 0;
		while (src[i] == c && src[i])
			i++;
		while (src[i] != c && src[i])
		{
			len++;
			i++;
		}
		split[count_line] = (char *)malloc(1 + len * sizeof(char));
		if (!split[count_line])
			return (0);
		ft_insert(split[count_line], src, i, len);
		count_line++;
	}
	split[count_line] = NULL;
	return (1);
}

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free (split[i]);
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		line;

	if (!s)
		return (NULL);
	line = ft_nbrword(s, c);
	split = (char **)malloc((line + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	if (!ft_create_split(split, s, c, line))
	{
		free_split(split);
		free(split);
		return (NULL);
	}
	return (split);
}
