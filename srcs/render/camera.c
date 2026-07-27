/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 12:47:36 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:01:47 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

/**
 * @brief Build the camera's orthonormal basis (dir, right, up).
 *
 * Normalizes the view direction and derives the right/up vectors. Falls back
 * to a world-up of (0,0,1) when the camera looks nearly straight up or down,
 * to avoid a degenerate cross product.
 * @param cam Camera whose dir/right/up fields are computed in place.
 */
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

/**
 * @brief Compute the primary ray passing through a given pixel.
 *
 * Maps the pixel to normalized screen coordinates, applies the FOV scale and
 * the aspect ratio, then builds the ray from the camera basis.
 * @param cam Camera with an initialized basis (see ft_setup_camera).
 * @param x Pixel column.
 * @param y Pixel row.
 * @return A ray originating at the camera with a normalized direction.
 */
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
