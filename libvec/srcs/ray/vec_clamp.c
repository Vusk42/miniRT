/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_clamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 16:48:00 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/22 18:36:16 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

static double	clampd(double x, double lo, double hi)
{
	if (x < lo)
		return (lo);
	if (x > hi)
		return (hi);
	return (x);
}

/**
 * @brief Clamp each component of a vector to the range [lo, hi].
 * @param v Vector to clamp.
 * @param lo Lower bound.
 * @param hi Upper bound.
 * @return The vector with each component clamped to [lo, hi].
 */
t_vec3	vec_clamp(t_vec3 v, double lo, double hi)
{
	double	x;
	double	y;
	double	z;

	x = clampd(v.x, lo, hi);
	y = clampd(v.y, lo, hi);
	z = clampd(v.z, lo, hi);
	return (vec_new(x, y, z));
}
