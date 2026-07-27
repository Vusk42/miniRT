/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 15:33:27 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:01:28 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Consume an optional leading '+' or '-' sign.
 * @param s Pointer to the parse cursor, advanced past the sign if present.
 * @return -1 for a '-' sign, 1 otherwise.
 */
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

/**
 * @brief Accumulate the integer part digits into a value.
 * @param s Parse cursor, advanced past the consumed digits.
 * @param acc Accumulator updated with the parsed digits.
 * @return The number of digits consumed.
 */
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

/**
 * @brief Accumulate the fractional part digits and their power-of-ten scale.
 * @param s Parse cursor, advanced past the consumed digits.
 * @param frac Accumulator for the fractional digits (as an integer).
 * @return The scale (10^n) to divide `frac` by; 1.0 if no digit was read.
 */
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

/**
 * @brief Parse a full decimal number from a string with strict validation.
 * @param s String to parse (optional sign, digits, optional fraction).
 * @param out Output value on success.
 * @return 0 on success, 1 if the string is empty or not a valid number.
 */
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
