/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 18:28:14 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 19:37:23 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Translate the camera along its own basis from a movement key.
 *
 * W/S move along the view direction, A/D along the right axis and Q/E along
 * the up axis, each by CAM_MOVE_STEP.
 * @param cam Camera whose position is updated in place.
 * @param key MLX42 key symbol of the pressed key.
 * @return 1 if the key mapped to a move, 0 otherwise.
 */
int	ft_cam_move(t_camera *cam, int key)
{
	if (key == MLX_KEY_W)
		cam->pos = vec_add(cam->pos, vec_scale(cam->dir, CAM_MOVE_STEP));
	else if (key == MLX_KEY_S)
		cam->pos = vec_sub(cam->pos, vec_scale(cam->dir, CAM_MOVE_STEP));
	else if (key == MLX_KEY_D)
		cam->pos = vec_add(cam->pos, vec_scale(cam->right, CAM_MOVE_STEP));
	else if (key == MLX_KEY_A)
		cam->pos = vec_sub(cam->pos, vec_scale(cam->right, CAM_MOVE_STEP));
	else if (key == MLX_KEY_E)
		cam->pos = vec_add(cam->pos, vec_scale(cam->up, CAM_MOVE_STEP));
	else if (key == MLX_KEY_Q)
		cam->pos = vec_sub(cam->pos, vec_scale(cam->up, CAM_MOVE_STEP));
	else
		return (0);
	return (1);
}

/**
 * @brief Rotate the camera view direction from an arrow key.
 *
 * Left/right yaw around the world up axis, up/down pitch around the camera
 * right axis, each by CAM_ROT_STEP radians. The basis is rebuilt on the next
 * render.
 * @param cam Camera whose dir is updated in place.
 * @param key MLX42 key symbol of the pressed key.
 * @return 1 if the key mapped to a rotation, 0 otherwise.
 */
int	ft_cam_rotate(t_camera *cam, int key)
{
	t_vec3	up;

	up = vec_new(0.0, 1.0, 0.0);
	if (key == MLX_KEY_LEFT)
		cam->dir = ft_rotate_axis(cam->dir, up, CAM_ROT_STEP);
	else if (key == MLX_KEY_RIGHT)
		cam->dir = ft_rotate_axis(cam->dir, up, -CAM_ROT_STEP);
	else if (key == MLX_KEY_UP)
		cam->dir = ft_rotate_axis(cam->dir, cam->right, CAM_ROT_STEP);
	else if (key == MLX_KEY_DOWN)
		cam->dir = ft_rotate_axis(cam->dir, cam->right, -CAM_ROT_STEP);
	else
		return (0);
	return (1);
}

/**
 * @brief Dispatch a key press to the camera, the selection or the object.
 *
 * Camera moves/rotations win first, then TAB cycles the selection, then the
 * remaining keys act on the selected object (translate / rotate / resize).
 * @param rt Main context (camera, object list and current selection).
 * @param key MLX42 key symbol of the pressed key.
 * @return 1 if the scene changed and must be re-rendered, 0 otherwise.
 */
int	ft_handle_key(t_rt *rt, int key)
{
	t_camera	*cam;
	t_object	*sel;

	cam = &rt->scene.camera;
	if (ft_cam_move(cam, key) || ft_cam_rotate(cam, key))
		return (1);
	if (key == MLX_KEY_TAB)
		return (ft_select_next(&rt->scene));
	sel = rt->scene.selected;
	if (sel == NULL)
		return (0);
	return (ft_obj_move(sel, key) || ft_obj_rotate(sel, key)
		|| ft_obj_resize(sel, key));
}
