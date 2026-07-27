/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_shapes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 16:28:25 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:01:55 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

/**
 * @brief Ray/plane intersection.
 * @param pl Plane to test.
 * @param ray Ray to test.
 * @return Distance t to the intersection, or -1.0 if the ray is parallel to
 * the plane or hits it behind the origin.
 */
double	ft_hit_plane(const t_plane *pl, t_ray ray)
{
	double	denom;
	double	t;

	denom = vec_dot(ray.dir, pl->normal);
	if (fabs(denom) < RT_EPSILON_PARALLEL)
		return (-1.0);
	t = vec_dot(vec_sub(pl->point, ray.origin), pl->normal) / denom;
	if (t > RT_EPSILON)
		return (t);
	return (-1.0);
}

/**
 * @brief Surface normal of a cylinder at a given point.
 *
 * Returns the axis (or its opposite) when the point lies on a cap, otherwise
 * the radial direction from the axis to the point on the side.
 * @param cy Cylinder.
 * @param point Point on the cylinder surface.
 * @return The unit normal at that point.
 */
static t_vec3	ft_cylinder_normal(const t_cylinder *cy, t_vec3 point)
{
	t_vec3	v;
	double	m;

	v = vec_sub(point, cy->center);
	m = vec_dot(v, cy->axis);
	if (m > cy->height / 2.0 - RT_EPSILON_CAP)
		return (cy->axis);
	if (m < -cy->height / 2.0 + RT_EPSILON_CAP)
		return (vec_neg(cy->axis));
	v = vec_normalize(vec_sub(v, vec_scale(cy->axis, m)));
	return (v);
}

/**
 * @brief Surface normal of any object at a given point.
 * @param obj Object hit (sphere, plane or cylinder).
 * @param point Point on the object surface.
 * @return The unit normal at that point.
 */
t_vec3	ft_object_normal(const t_object *obj, t_vec3 point)
{
	if (obj->type == OBJ_SPHERE)
		return (vec_normalize(vec_sub(point, obj->shape.sp.center)));
	if (obj->type == OBJ_PLANE)
		return (obj->shape.pl.normal);
	return (ft_cylinder_normal(&obj->shape.cy, point));
}
