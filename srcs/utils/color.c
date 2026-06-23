/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 23:14:48 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/23 23:22:14 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static uint32_t	ft_channel(double v)
{
	if (v < 0.0)
		v = 0.0;
	if (v > 1.0)
		v = 1.0;
	return ((uint32_t)(v * 255.0 + 0.5));
}

uint32_t	ft_color_to_int(t_color c)
{
	return ((ft_channel(c.x) << 24) | (ft_channel(c.y) << 16)
		| (ft_channel(c.z) << 8) | 0xFF);
}
