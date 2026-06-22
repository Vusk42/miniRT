/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:24:10 by marudlof          #+#    #+#             */
/*   Updated: 2025/12/01 14:55:29 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/print.h"

int	ft_putendl_fd(const char *s, int fd)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
	i += write(fd, "\n", 1);
	return (i);
}
