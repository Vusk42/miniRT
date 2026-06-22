/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:24:46 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 17:01:47 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../../includes/ft/print.h"

static int	ft_nbrlen_base(int n, int base)
{
	int	i;

	i = 1;
	while (n >= base)
	{
		n /= base;
		i++;
	}
	return (i);
}

int	ft_putnbr_fd(int n, int fd)
{
	const char	*base = "0123456789";
	int			nbr_len;

	nbr_len = 0;
	if (n == INT_MIN)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		nbr_len += ft_putnbr_fd(-n, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putnbr_fd((n % 10), fd);
	}
	else
		write(fd, &base[n], 1);
	nbr_len += ft_nbrlen_base(n, 10);
	return (nbr_len);
}
