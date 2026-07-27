/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 23:14:48 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:02:05 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Convert one normalized color component to an 8-bit channel.
 * @param v Component value, clamped to [0, 1].
 * @return The component mapped to [0, 255] with rounding.
 */
static uint32_t	ft_channel(double v)
{
	if (v < 0.0)
		v = 0.0;
	if (v > 1.0)
		v = 1.0;
	return ((uint32_t)(v * 255.0 + 0.5));
}

/**
 * @brief Pack a normalized RGB color into a 0xRRGGBBAA integer for MLX42.
 * @param c Color with components in [0, 1].
 * @return The color as a 32-bit RGBA value with alpha forced to 0xFF.
 */
uint32_t	ft_color_to_int(t_color c)
{
	return ((ft_channel(c.x) << 24) | (ft_channel(c.y) << 16)
		| (ft_channel(c.z) << 8) | 0xFF);
}
