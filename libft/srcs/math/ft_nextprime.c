/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nextprime.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:05:58 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 16:59:45 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/math.h"

int	ft_nextprime(int nb)
{
	if (!ft_isprime(nb))
		return (ft_nextprime(++nb));
	return (nb);
}
