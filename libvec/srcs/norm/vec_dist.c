/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_dist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 16:48:00 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/22 17:47:20 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

/**
 * @brief Euclidean distance between two points.
 * @param a First point.
 * @param b Second point.
 * @return |a - b|.
 */
double	vec_dist(t_vec3 a, t_vec3 b)
{
	t_vec3	delta;
	double	dist;

	delta = vec_sub(a, b);
	dist = vec_len(delta);
	return (dist);
}
