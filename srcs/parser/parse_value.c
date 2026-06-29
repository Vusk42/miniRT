/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 15:33:27 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/29 12:30:54 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	ft_parse_sign(const char **s)
{
	if (**s == '-')
	{
		(*s)++;
		return (-1);
	}
	if (**s == '+')
		(*s)++;
	return (1);
}

static int	ft_parse_digits(const char **s, double *acc)
{
	int	count;

	count = 0;
	while (ft_isdigit(**s) != 0)
	{
		*acc = *acc * 10.0 + (**s - '0');
		(*s)++;
		count++;
	}
	return (count);
}

static double	ft_parse_frac(const char **s, double *frac)
{
	double	scale;

	scale = 1.0;
	while (ft_isdigit(**s) != 0)
	{
		*frac = *frac * 10.0 + (**s - '0');
		scale = scale * 10.0;
		(*s)++;
	}
	return (scale);
}

int	ft_parse_double(const char *s, double *out)
{
	double	value;
	double	frac;
	double	scale;
	int		sign;
	int		digits;

	if (!s || *s == '\0')
		return (1);
	value = 0.0;
	sign = ft_parse_sign(&s);
	digits = ft_parse_digits(&s, &value);
	if (*s == '.')
	{
		s++;
		frac = 0.0;
		scale = ft_parse_frac(&s, &frac);
		if (scale == 1.0)
			return (1);
		value = value + frac / scale;
		digits++;
	}
	if (digits == 0 || *s != '\0')
		return (1);
	*out = value * sign;
	return (0);
}
