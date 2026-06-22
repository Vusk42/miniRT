/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_lerp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 16:48:00 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/22 18:39:31 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

/**
 * @brief Linear interpolation between two vectors.
 * @param a Start vector (returned for t = 0).
 * @param b End vector (returned for t = 1).
 * @param t Interpolation factor, typically in [0, 1].
 * @return a + (b - a) * t.
 */
t_vec3	vec_lerp(t_vec3 a, t_vec3 b, double t)
{
	t_vec3	delta;
	t_vec3	step;

	delta = vec_sub(b, a);
	step = vec_scale(delta, t);
	return (vec_add(a, step));
}
