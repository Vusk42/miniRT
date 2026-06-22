/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:34:01 by marudlof          #+#    #+#             */
/*   Updated: 2025/12/01 14:55:40 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/print.h"

int	ft_puthexa_fd(long long int n, const char format, int fd)
{
	size_t	nbr_len;

	nbr_len = 0;
	if (format == 'p')
		nbr_len += write(fd, "0x", 2);
	if (format == 'X')
		nbr_len += ft_putnbr_base_fd(n, "0123456789ABCDEF", fd);
	if (format == 'x' || format == 'p')
		nbr_len += ft_putnbr_base_fd(n, "0123456789abcdef", fd);
	return (nbr_len);
}
