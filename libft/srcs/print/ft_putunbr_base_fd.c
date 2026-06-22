/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_base_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:48:52 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 17:02:09 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../../includes/ft/print.h"
#include "../../includes/ft/string.h"

int	ft_putunbr_base_fd(unsigned long long int n, const char *base, int fd)
{
	unsigned long long int	base_len;
	int						nbr_len;

	nbr_len = 0;
	base_len = ft_strlen(base);
	if (n >= base_len)
	{
		ft_putunbr_base_fd(n / base_len, base, fd);
		ft_putunbr_base_fd(n % base_len, base, fd);
	}
	else
		write(fd, &base[n], 1);
	nbr_len += ft_unbrlen_base(n, base_len);
	return (nbr_len);
}
