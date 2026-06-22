/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:44:36 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 17:00:52 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../includes/ft/print.h"
#include "../../includes/ft/string.h"

static int	ft_handleprint(va_list args, const char format)
{
	unsigned long	ptr;
	int				rtn;

	rtn = -1;
	if (format == 'c')
		rtn = ft_putchar_fd(va_arg(args, int), 1);
	else if (format == 's')
		rtn = ft_putstr_fd(va_arg(args, char *), 1);
	if (format == 'p')
	{
		ptr = va_arg(args, unsigned long);
		if (ptr)
			rtn = ft_putuhexa_fd(ptr, format, 1);
		else
			rtn = ft_putstr_fd("(nil)", 1);
	}
	else if (format == 'd' || format == 'i')
		rtn = ft_putnbr_fd(va_arg(args, int), 1);
	else if (format == 'u')
		rtn = ft_putunbr_base_fd(va_arg(args, unsigned int), "0123456789", 1);
	else if (format == 'x' || format == 'X')
		rtn = ft_putuhexa_fd(va_arg(args, unsigned int), format, 1);
	else if (format == '%')
		rtn = ft_putchar_fd('%', 1);
	return (rtn);
}

int	ft_printf(const char *format, ...)
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
			rtn += ft_handleprint(args, format[i + 1]);
			i++;
		}
		else
			rtn += ft_putchar_fd(format[i], 1);
		i++;
	}
	va_end(args);
	return (rtn);
}
