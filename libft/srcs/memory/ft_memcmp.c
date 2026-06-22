/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:00:20 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 17:00:35 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/memory.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]) > 0)
			return (1);
		if ((((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]) < 0)
			return (-1);
		i++;
	}
	return (0);
}
