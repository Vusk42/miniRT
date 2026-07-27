/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 18:15:07 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 19:23:44 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

/**
 * @brief Rotate a vector around an arbitrary axis (Rodrigues' formula).
 * @param v Vector to rotate.
 * @param axis Rotation axis (normalized internally).
 * @param angle Rotation angle in radians.
 * @return The rotated vector.
 */
t_vec3	ft_rotate_axis(t_vec3 v, t_vec3 axis, double angle)
{
	t_vec3	k;
	t_vec3	res;
	double	c;
	double	s;

	k = vec_normalize(axis);
	c = cos(angle);
	s = sin(angle);
	res = vec_scale(v, c);
	res = vec_add(res, vec_scale(vec_cross(k, v), s));
	res = vec_add(res, vec_scale(k, vec_dot(k, v) * (1.0 - c)));
	return (res);
}
