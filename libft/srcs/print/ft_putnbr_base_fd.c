/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 21:11:35 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 17:01:32 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/print.h"
#include "../../includes/ft/string.h"
#include <limits.h>

int	ft_putnbr_base_fd(long long int n, const char *base, int fd)
{
	int	base_len;
	int	n_len;

	n_len = 0;
	base_len = ft_strlen(base);
	if (n == LLONG_MIN)
	{
		write(fd, "-9223372036854775807", 20);
		return (20);
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n_len += ft_putnbr_base_fd(-n, base, fd);
	}
	if (n >= base_len)
	{
		ft_putnbr_base_fd(n / base_len, base, fd);
		ft_putnbr_base_fd(n % base_len, base, fd);
	}
	else
		write(fd, &base[n], 1);
	n_len += ft_nbrlen_base(n, base_len);
	return (n_len);
}
