/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 16:48:00 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/22 17:36:01 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

/**
 * @brief Multiply a vector by a scalar.
 * @param v Vector to rescale.
 * @param t Scale factor.
 * @return The vector v * t.
 */
t_vec3	vec_scale(t_vec3 v, double t)
{
	t_vec3	vector;

	vector.x = v.x * t;
	vector.y = v.y * t;
	vector.z = v.z * t;
	return (vector);
}
