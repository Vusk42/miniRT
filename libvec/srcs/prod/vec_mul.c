/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mul.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 16:48:00 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/22 18:25:09 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

/**
 * @brief Component-wise product (Hadamard product).
 * @param a First vector.
 * @param b Second vector.
 * @return {a.x*b.x, a.y*b.y, a.z*b.z}. Handy to modulate colors.
 */
t_vec3	vec_mul(t_vec3 a, t_vec3 b)
{
	t_vec3	vector;

	vector.x = a.x * b.x;
	vector.y = a.y * b.y;
	vector.z = a.z * b.z;
	return (vector);
}
