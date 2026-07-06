/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 12:47:36 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/06 15:01:50 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

void	ft_setup_camera(t_camera *cam)
{
	t_vec3	world_up;
	t_vec3	forward;

	forward = vec_normalize(cam->dir);
	world_up = vec_new(0.0, 1.0, 0.0);
	if (fabs(vec_dot(forward, world_up)) > 0.999)
		world_up = vec_new(0.0, 0.0, 1.0);
	cam->dir = forward;
	cam->right = vec_normalize(vec_cross(world_up, forward));
	cam->up = vec_cross(forward, cam->right);
}

t_ray	ft_primary_ray(const t_camera *cam, uint32_t x, uint32_t y)
{
	t_ray	ray;
	double	scale;
	double	px;
	double	py;

	scale = tan(cam->fov * 0.5 * M_PI / 180.0);
	px = (2.0 * ((double)x + 0.5) / WIN_W - 1.0) * ((double)WIN_W / WIN_H)
		* scale;
	py = (1.0 - 2.0 * ((double)y + 0.5) / WIN_H) * scale;
	ray.origin = cam->pos;
	ray.dir = vec_normalize(vec_add(cam->dir,
				vec_add(vec_scale(cam->right, px), vec_scale(cam->up, py))));
	return (ray);
}
