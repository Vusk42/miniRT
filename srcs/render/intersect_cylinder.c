/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 16:28:13 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:01:53 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

/**
 * @brief Return the smallest of two distances, ignoring negative ones.
 * @param a First distance (negative means "no hit").
 * @param b Second distance (negative means "no hit").
 * @return The smallest non-negative value, or a negative value if both miss.
 */
static double	ft_min_pos(double a, double b)
{
	if (a < 0.0)
		return (b);
	if (b < 0.0)
		return (a);
	if (a < b)
		return (a);
	return (b);
}

/**
 * @brief Validate a side-surface root against the cylinder's height band.
 * @param cy Cylinder.
 * @param ray Ray being tested.
 * @param t Candidate distance along the ray.
 * @return t if the hit lies within [-height/2, height/2] along the axis and
 * is in front of the origin, -1.0 otherwise.
 */
static double	ft_band_t(const t_cylinder *cy, t_ray ray, double t)
{
	double	m;

	if (t <= RT_EPSILON)
		return (-1.0);
	m = vec_dot(ray.dir, cy->axis) * t
		+ vec_dot(vec_sub(ray.origin, cy->center), cy->axis);
	if (m < -cy->height / 2.0 || m > cy->height / 2.0)
		return (-1.0);
	return (t);
}

/**
 * @brief Ray intersection with the infinite side surface, bounded by height.
 * @param cy Cylinder.
 * @param ray Ray to test.
 * @return Distance to the nearest valid side hit, or -1.0 if none.
 */
static double	ft_hit_side(const t_cylinder *cy, t_ray ray)
{
	t_vec3	x;
	double	k[3];
	double	d;
	double	t[2];

	x = vec_sub(ray.origin, cy->center);
	k[0] = vec_len2(ray.dir) - pow(vec_dot(ray.dir, cy->axis), 2.0);
	k[1] = 2.0 * (vec_dot(ray.dir, x)
			- vec_dot(ray.dir, cy->axis) * vec_dot(x, cy->axis));
	k[2] = vec_len2(x) - pow(vec_dot(x, cy->axis), 2.0)
		- cy->radius * cy->radius;
	d = k[1] * k[1] - 4.0 * k[0] * k[2];
	if (d < 0.0)
		return (-1.0);
	t[0] = ft_band_t(cy, ray, (-k[1] - sqrt(d)) / (2.0 * k[0]));
	t[1] = ft_band_t(cy, ray, (-k[1] + sqrt(d)) / (2.0 * k[0]));
	return (ft_min_pos(t[0], t[1]));
}

/**
 * @brief Ray intersection with one of the cylinder's disk caps.
 * @param cy Cylinder.
 * @param ray Ray to test.
 * @param sign +1.0 for the top cap, -1.0 for the bottom cap.
 * @return Distance to the cap hit if inside the disk radius, -1.0 otherwise.
 */
static double	ft_hit_cap(const t_cylinder *cy, t_ray ray, double sign)
{
	t_vec3	pc;
	t_vec3	p;
	double	denom;
	double	t;

	pc = vec_add(cy->center, vec_scale(cy->axis, sign * cy->height / 2.0));
	denom = vec_dot(ray.dir, cy->axis);
	if (fabs(denom) < RT_EPSILON_PARALLEL)
		return (-1.0);
	t = vec_dot(vec_sub(pc, ray.origin), cy->axis) / denom;
	if (t <= RT_EPSILON)
		return (-1.0);
	p = vec_add(ray.origin, vec_scale(ray.dir, t));
	if (vec_len2(vec_sub(p, pc)) > cy->radius * cy->radius)
		return (-1.0);
	return (t);
}

/**
 * @brief Ray/cylinder intersection (side surface plus both caps).
 * @param cy Cylinder to test.
 * @param ray Ray to test.
 * @return Distance t to the nearest intersection, or -1.0 if the ray misses.
 */
double	ft_hit_cylinder(const t_cylinder *cy, t_ray ray)
{
	double	side;
	double	caps;

	side = ft_hit_side(cy, ray);
	caps = ft_min_pos(ft_hit_cap(cy, ray, 1.0), ft_hit_cap(cy, ray, -1.0));
	return (ft_min_pos(side, caps));
}
