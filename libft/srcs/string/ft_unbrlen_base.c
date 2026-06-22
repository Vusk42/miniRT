/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unbrlen_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:52:08 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 17:03:43 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/string.h"

size_t	ft_unbrlen_base(unsigned long long int n, size_t base)
{
	size_t	i;

	i = 1;
	while (n >= (unsigned long long int)base)
	{
		n /= base;
		i++;
	}
	return (i);
}
