/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 16:48:00 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/22 17:28:19 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

/**
 * @brief Build a 3D vector from its components.
 * @param x X-axis component.
 * @param y Y-axis component.
 * @param z Z-axis component.
 * @return The vector {x, y, z}.
 */
t_vec3	vec_new(double x, double y, double z)
{
	t_vec3	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}
