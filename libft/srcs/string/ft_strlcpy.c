/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:42:16 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 17:03:02 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/string.h"

size_t	ft_strlcpy(char *dst, char const *src, size_t size)
{
	size_t	i;

	i = 0;
	while (size != 0 && i < size - 1 && src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < size)
		dst[i] = 0;
	while (src[i])
		i++;
	return (i);
}
