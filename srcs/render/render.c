/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 23:15:09 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:14:24 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_types.h"

/**
 * @brief Background gradient color derived from a ray direction.
 * @param dir Normalized ray direction.
 * @return A color mapping each direction component from [-1,1] to [0,1].
 */
static t_color	ft_ray_dir_color(t_vec3 dir)
{
	t_color	ray;

	ray = vec_new(0.5 * (dir.x + 1.0), 0.5 * (dir.y + 1.0),
			0.5 * (dir.z + 1.0));
	return (ray);
}

/**
 * @brief Trace a ray through the scene and return its color.
 * @param scene Scene to test against.
 * @param ray Ray to trace.
 * @return The hit object's color, or the background gradient if nothing is hit.
 */
static t_color	ft_trace(t_scene *scene, t_ray ray)
{
	t_hit	hit;

	if (ft_closest_hit(scene, ray, &hit))
		return (ft_lighting(scene, &hit));
	return (ft_ray_dir_color(ray.dir));
}

/**
 * @brief Render the whole scene into the MLX image, one ray per pixel.
 * @param rt Main context holding the scene and the target image.
 */
void	ft_render(t_rt *rt)
{
	uint32_t	x;
	uint32_t	y;
	t_ray		ray;

	ft_setup_camera(&rt->scene.camera);
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			ray = ft_primary_ray(&rt->scene.camera, x, y);
			mlx_put_pixel(rt->img, x, y,
				ft_color_to_int(ft_trace(&rt->scene, ray)));
			x++;
		}
		y++;
	}
}
