/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 23:15:09 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/07 10:00:34 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_types.h"

static t_color	ft_ray_dir_color(t_vec3 dir)
{
	t_color	ray;

	ray = vec_new(0.5 * (dir.x + 1.0), 0.5 * (dir.y + 1.0),
			0.5 * (dir.z + 1.0));
	return (ray);
}

static t_color	ft_trace(t_scene *scene, t_ray ray)
{
	t_hit	hit;

	if (ft_closest_hit(scene, ray, &hit))
		return (hit.color);
	return (ft_ray_dir_color(ray.dir));
}

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
