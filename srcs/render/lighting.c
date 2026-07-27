/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:30:12 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:12:56 by marudlof         ###   ########.fr       */
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
 * @brief Simplified Phong shading (ambient + diffuse) at a hit point.
 * @param scene Scene holding the ambient light and the light source.
 * @param hit Hit record filled by the intersection stage.
 * @return The final surface color, clamped to [0, 1].
 */
t_color	ft_lighting(t_scene *scene, t_hit *hit)
{
	t_color	color;

	color = vec_add(ft_ambient(scene, hit->color),
			ft_diffuse(scene, hit, hit->color));
	return (vec_clamp(color, 0.0, 1.0));
}
