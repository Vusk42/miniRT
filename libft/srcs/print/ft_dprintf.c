/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 16:26:59 by marudlof          #+#    #+#             */
/*   Updated: 2026/04/15 16:30:28 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../includes/ft/print.h"
#include "../../includes/ft/string.h"

static int	ft_handleprint(int fd, va_list args, const char format)
{
	unsigned long	ptr;
	int				rtn;

	rtn = -1;
	if (format == 'c')
		rtn = ft_putchar_fd(va_arg(args, int), fd);
	else if (format == 's')
		rtn = ft_putstr_fd(va_arg(args, char *), fd);
	if (format == 'p')
	{
		ptr = va_arg(args, unsigned long);
		if (ptr)
			rtn = ft_putuhexa_fd(ptr, format, fd);
		else
			rtn = ft_putstr_fd("(nil)", fd);
	}
	else if (format == 'd' || format == 'i')
		rtn = ft_putnbr_fd(va_arg(args, int), fd);
	else if (format == 'u')
		rtn = ft_putunbr_base_fd(va_arg(args, unsigned int), "0123456789", fd);
	else if (format == 'x' || format == 'X')
		rtn = ft_putuhexa_fd(va_arg(args, unsigned int), format, fd);
	else if (format == '%')
		rtn = ft_putchar_fd('%', fd);
	return (rtn);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		rtn;

	i = 0;
	rtn = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && ft_strchr("cspdiuxX%", format[i + 1]) != 0)
		{
			rtn += ft_handleprint(fd, args, format[i + 1]);
			i++;
		}
		else
			rtn += ft_putchar_fd(format[i], fd);
		i++;
	}
	va_end(args);
	return (rtn);
}
