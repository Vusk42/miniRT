/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_reflect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 16:48:00 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/22 18:45:26 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

/**
 * @brief Reflect a vector about a normal.
 * @param v Incident vector.
 * @param n Surface normal (must be normalized).
 * @return The reflected vector: v - 2 * (v . n) * n.
 */
t_vec3	vec_reflect(t_vec3 v, t_vec3 n)
{
	double	dot;
	t_vec3	proj;

	dot = vec_dot(v, n);
	proj = vec_scale(n, 2.0 * dot);
	return (vec_sub(v, proj));
}
