/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 16:48:00 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/22 18:44:29 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

/**
 * @brief Add two vectors component-wise.
 * @param a First vector.
 * @param b Second vector.
 * @return The vector a + b.
 */
t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	t_vec3	vector;

	vector.x = a.x + b.x;
	vector.y = a.y + b.y;
	vector.z = a.z + b.z;
	return (vector);
}
