/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 21:16:38 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 17:02:37 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/string.h"
#include "../../includes/ft/math.h"

size_t	ft_nbrlen_base(long long int n, size_t base)
{
	size_t	i;

	n = ft_abs(n);
	i = 1;
	while (n >= (long long int)base)
	{
		n /= base;
		i++;
	}
	return (i);
}
