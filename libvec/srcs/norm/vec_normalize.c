/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 16:48:00 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/22 17:58:20 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

/**
 * @brief Normalize a vector (length brought back to 1).
 * @param v Vector to normalize.
 * @return The unit vector with the same direction (v / |v|).
 * @warning Undefined behavior if v is the null vector (division by zero).
 */
t_vec3	vec_normalize(t_vec3 v)
{
	t_vec3	vector;
	double	magnitude;

	magnitude = vec_len(v);
	vector.x = v.x / magnitude;
	vector.y = v.y / magnitude;
	vector.z = v.z / magnitude;
	return (vector);
}
