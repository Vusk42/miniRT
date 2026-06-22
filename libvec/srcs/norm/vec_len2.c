/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_len2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 16:48:00 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/22 17:50:15 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

/**
 * @brief Squared norm (avoids the sqrt call).
 * @param v Vector to measure.
 * @return x*x + y*y + z*z.
 * @note Prefer it to compare distances without the sqrt cost.
 */
double	vec_len2(t_vec3 v)
{
	double	length;

	length = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	return (length);
}
