/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_dot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 16:48:00 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/22 18:29:42 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

/**
 * @brief Dot product of two vectors.
 * @param a First vector.
 * @param b Second vector.
 * @return a.x*b.x + a.y*b.y + a.z*b.z. Zero if a and b are orthogonal.
 */
double	vec_dot(t_vec3 a, t_vec3 b)
{
	double	product;

	product = a.x * b.x + a.y * b.y + a.z * b.z;
	return (product);
}
