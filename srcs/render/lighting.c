/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:30:12 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:41:58 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

/**
 * @brief Ambient contribution: the scene's ambient light modulating a color.
 * @param scene Scene holding the ambient light.
 * @param base Surface color at the hit point.
 * @return The base color scaled by the ambient ratio and color.
 */
static t_color	ft_ambient(t_scene *scene, t_color base)
{
	t_color	amb;

	amb = vec_scale(scene->ambient.color, scene->ambient.ratio);
	return (vec_mul(base, amb));
}

/**
 * @brief Diffuse (Lambert) contribution from the scene's single light.
 * @param scene Scene holding the light.
 * @param hit Hit record (uses point and normal).
 * @param base Surface color at the hit point.
 * @return The diffuse color, zero when the surface faces away from the light.
 */
static t_color	ft_diffuse(t_scene *scene, t_hit *hit, t_color base)
{
	t_vec3	ldir;
	double	diff;
	t_color	light;

	ldir = vec_normalize(vec_sub(scene->light.pos, hit->point));
	diff = vec_dot(hit->normal, ldir);
	if (diff < 0.0)
		diff = 0.0;
	light = vec_scale(scene->light.color, scene->light.ratio * diff);
	return (vec_mul(base, light));
}

/**
 * @brief Test whether the hit point is shadowed from the scene light.
 *
 * Casts a ray from the point towards the light and reports a block if any
 * object lies strictly between them. The origin is nudged along the normal
 * to avoid self-shadowing (shadow acne).
 * @param scene Scene holding the light and the object list.
 * @param hit Hit record (uses point and normal).
 * @return 1 if an object occludes the light, 0 otherwise.
 */
static int	ft_in_shadow(t_scene *scene, t_hit *hit)
{
	t_ray	sray;
	t_vec3	ldir;
	double	ldist;
	double	t;
	t_list	*node;

	ldir = vec_sub(scene->light.pos, hit->point);
	ldist = vec_len(ldir);
	sray.dir = vec_normalize(ldir);
	sray.origin = vec_add(hit->point, vec_scale(hit->normal, RT_EPSILON));
	node = scene->objects;
	while (node != NULL)
	{
		t = ft_hit_object(node->content, sray);
		if (t > RT_EPSILON && t < ldist)
			return (1);
		node = node->next;
	}
	return (0);
}

/**
 * @brief Simplified Phong shading (ambient + diffuse) at a hit point.
 *
 * The diffuse term is dropped when the point is shadowed, so only the
 * ambient term remains.
 * @param scene Scene holding the ambient light and the light source.
 * @param hit Hit record filled by the intersection stage.
 * @return The final surface color, clamped to [0, 1].
 */
t_color	ft_lighting(t_scene *scene, t_hit *hit)
{
	t_color	color;

	color = ft_ambient(scene, hit->color);
	if (!ft_in_shadow(scene, hit))
		color = vec_add(color, ft_diffuse(scene, hit, hit->color));
	return (vec_clamp(color, 0.0, 1.0));
}
