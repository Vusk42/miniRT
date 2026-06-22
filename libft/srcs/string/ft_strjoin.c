/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:38:37 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 17:02:53 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/string.h"

static void	ft_strjcat(char *join, char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1);
	total_len += ft_strlen(s2);
	join = (char *)malloc((total_len + 1) * sizeof(char));
	if (!join)
		return (NULL);
	ft_strjcat(join, s1, s2);
	return (join);
}
