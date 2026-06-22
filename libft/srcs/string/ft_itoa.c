/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:54:30 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 17:02:30 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/string.h"

static int	ft_sizeinteger(int n)
{
	int		size;
	long	nbr;

	nbr = n;
	size = 1;
	if (nbr < 0)
	{
		nbr = -nbr;
		size++;
	}
	while (nbr >= 10)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	int		len;
	int		i;

	len = ft_sizeinteger(n);
	str = (char *)malloc(1 + len * sizeof(char));
	if (!str)
		return (NULL);
	nbr = n;
	if (nbr < 0)
	{
		nbr = -nbr;
		str[0] = '-';
	}
	i = 1;
	str[len] = '\0';
	while (nbr >= 10)
	{
		str[len - i] = (nbr % 10) + '0';
		nbr /= 10;
		i++;
	}
	str[len - i] = ((nbr % 10) + '0');
	return (str);
}
