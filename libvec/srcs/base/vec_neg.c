/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_neg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 16:48:00 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/22 17:35:06 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

/**
 * @brief Compute the opposite of a vector (reversed direction).
 * @param v Vector to negate.
 * @return The vector -v.
 */
t_vec3	vec_neg(t_vec3 v)
{
	t_vec3	vector;

	vector.x = -v.x;
	vector.y = -v.y;
	vector.z = -v.z;
	return (vector);
}
