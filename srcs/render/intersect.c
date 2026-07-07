/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 15:25:23 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/07 09:59:50 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

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

static void	ft_fill_hit(const t_object *obj, t_ray ray, t_hit *hit)
{
	hit->point = vec_add(ray.origin, vec_scale(ray.dir, hit->t));
	hit->color = obj->color;
	hit->normal = ft_object_normal(obj, hit->point);
}

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
