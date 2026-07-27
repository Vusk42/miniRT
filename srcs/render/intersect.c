/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 15:25:23 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:01:51 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

/**
 * @brief Solve a*t^2 + b*t + c = 0 and return the nearest valid root.
 * @param a Quadratic coefficient.
 * @param b Linear coefficient.
 * @param c Constant coefficient.
 * @return The smallest root greater than RT_EPSILON, or -1.0 if none exists.
 */
static double	ft_solve_quad(double a, double b, double c)
{
	double	disc;
	double	sq;
	double	t0;
	double	t1;

	disc = b * b - 4.0 * a * c;
	if (disc < 0.0)
		return (-1.0);
	sq = sqrt(disc);
	t0 = (-b - sq) / (2.0 * a);
	t1 = (-b + sq) / (2.0 * a);
	if (t0 > RT_EPSILON)
		return (t0);
	if (t1 > RT_EPSILON)
		return (t1);
	return (-1.0);
}

/**
 * @brief Ray/sphere intersection.
 * @param sp Sphere to test.
 * @param ray Ray to test.
 * @return Distance t to the nearest intersection, or -1.0 if the ray misses.
 */
double	ft_hit_sphere(const t_sphere *sp, t_ray ray)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;

	oc = vec_sub(ray.origin, sp->center);
	a = vec_dot(ray.dir, ray.dir);
	b = 2.0 * vec_dot(oc, ray.dir);
	c = vec_dot(oc, oc) - sp->radius * sp->radius;
	return (ft_solve_quad(a, b, c));
}

/**
 * @brief Dispatch a ray/object test to the right primitive routine.
 * @param obj Object to test (sphere, plane or cylinder).
 * @param ray Ray to test.
 * @return Distance t to the nearest intersection, or -1.0 if the ray misses.
 */
double	ft_hit_object(const t_object *obj, t_ray ray)
{
	double	hit;
	if (obj->type == OBJ_SPHERE)
	{
		hit = ft_hit_sphere(&obj->shape.sp, ray);
		return (hit);
	}
	if (obj->type == OBJ_PLANE)
	{
		hit = ft_hit_plane(&obj->shape.pl, ray);
		return (hit);
	}
	hit = ft_hit_cylinder(&obj->shape.cy, ray);
	return (hit);
}

/**
 * @brief Fill the hit record once the closest object and its t are known.
 * @param obj Closest object hit.
 * @param ray Ray that produced the hit.
 * @param hit Hit record (its `t` must be set); point, color and normal
 * are computed here.
 */
static void	ft_fill_hit(const t_object *obj, t_ray ray, t_hit *hit)
{
	hit->point = vec_add(ray.origin, vec_scale(ray.dir, hit->t));
	hit->color = obj->color;
	hit->normal = ft_object_normal(obj, hit->point);
}

/**
 * @brief Find the closest object hit by a ray among all scene objects.
 * @param scene Scene holding the object list.
 * @param ray Ray to trace.
 * @param hit Output hit record, filled when an object is hit.
 * @return 1 if an object is hit, 0 otherwise.
 */
int	ft_closest_hit(t_scene *scene, t_ray ray, t_hit *hit)
{
	t_list		*node;
	t_object	*obj;
	t_object	*best;
	double		t;

	best = NULL;
	hit->t = RT_MAX_DIST;
	node = scene->objects;
	while (node != NULL)
	{
		obj = node->content;
		t = ft_hit_object(obj, ray);
		if (t > 0.0 && t < hit->t)
		{
			hit->t = t;
			best = obj;
		}
		node = node->next;
	}
	if (best == NULL)
		return (0);
	ft_fill_hit(best, ray, hit);
	return (1);
}
