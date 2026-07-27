/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 23:15:09 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/28 00:19:17 by marudlof         ###   ########.fr       */
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
	t_color	color;

	if (!ft_closest_hit(scene, ray, &hit))
		return (ft_ray_dir_color(ray.dir));
	color = ft_lighting(scene, &hit);
	if (hit.obj == scene->selected)
		color = vec_lerp(color, vec_new(1.0, 1.0, 1.0), 0.35);
	return (color);
}

/**
 * @brief Paint a step by step square of pixels with a single color.
 *
 * Blocks are clipped to the image bounds, so the right and bottom edges stay
 * correct when the window size is not a multiple of the step.
 * @param img Target MLX image.
 * @param xy Top-left corner of the block: xy[0] = column, xy[1] = row.
 * @param color Packed RGBA color to write.
 * @param step Block side length in pixels.
 */
static void	ft_fill_block(mlx_image_t *img, const uint32_t xy[2],
		uint32_t color, int step)
{
	uint32_t	i;
	uint32_t	j;

	j = 0;
	while (j < (uint32_t)step && xy[1] + j < WIN_H)
	{
		i = 0;
		while (i < (uint32_t)step && xy[0] + i < WIN_W)
		{
			mlx_put_pixel(img, xy[0] + i, xy[1] + j, color);
			i++;
		}
		j++;
	}
}

/**
 * @brief Render the scene into the MLX image, one ray per step by step block.
 *
 * A step of 1 traces every pixel (final quality); a larger step trades
 * resolution for speed by reusing one ray's color over a whole block, which
 * is what the draft render used while editing relies on.
 * @param rt Main context holding the scene and the target image.
 * @param step Block side length in pixels, clamped to at least 1.
 */
void	ft_render(t_rt *rt, int step)
{
	uint32_t	xy[2];
	t_ray		ray;
	t_color		color;

	if (step < 1)
		step = 1;
	ft_setup_camera(&rt->scene.camera);
	xy[1] = 0;
	while (xy[1] < WIN_H)
	{
		xy[0] = 0;
		while (xy[0] < WIN_W)
		{
			ray = ft_primary_ray(&rt->scene.camera, xy[0], xy[1]);
			color = ft_trace(&rt->scene, ray);
			ft_fill_block(rt->img, xy, ft_color_to_int(color), step);
			xy[0] += step;
		}
		xy[1] += step;
	}
}
