/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 13:40:27 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/28 00:19:28 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RENDER_H
# define RT_RENDER_H

# include "rt_types.h"

# define RT_MAX_DIST 1e30
# define RT_EPSILON 1e-4
# define RT_EPSILON_PARALLEL 1e-6
# define RT_EPSILON_CAP 1e-3
# define CAM_MOVE_STEP 1.0
# define CAM_ROT_STEP 0.05
# define OBJ_MOVE_STEP 1.0
# define OBJ_ROT_STEP 0.05
# define OBJ_RESIZE_STEP 0.5
# define RT_DRAFT_STEP 4
# define RT_REFINE_DELAY 0.15
# define RT_REFINE_MAX 1.0

int			ft_init_window(t_rt *rt);
void		ft_render(t_rt *rt, int step);
void		ft_setup_camera(t_camera *cam);
t_ray		ft_primary_ray(const t_camera *cam, uint32_t x, uint32_t y);
double		ft_hit_sphere(const t_sphere *sp, t_ray ray);
double		ft_hit_plane(const t_plane *pl, t_ray ray);
double		ft_hit_cylinder(const t_cylinder *cy, t_ray ray);
double		ft_hit_object(const t_object *obj, t_ray ray);
t_vec3		ft_object_normal(const t_object *obj, t_vec3 point);
int			ft_closest_hit(t_scene *scene, t_ray ray, t_hit *hit);
t_color		ft_lighting(t_scene *scene, t_hit *hit);
t_vec3		ft_rotate_axis(t_vec3 v, t_vec3 axis, double angle);
int			ft_cam_move(t_camera *cam, int key);
int			ft_cam_rotate(t_camera *cam, int key);
int			ft_obj_move(t_object *obj, int key);
int			ft_obj_rotate(t_object *obj, int key);
int			ft_obj_resize(t_object *obj, int key);
int			ft_select_next(t_scene *scene);
int			ft_handle_key(t_rt *rt, int key);
void		ft_key_hook(mlx_key_data_t keydata, void *param);
void		ft_loop_hook(void *param);
void		ft_close_hook(void *param);

uint32_t	ft_color_to_int(t_color c);
void		ft_cleanup(t_rt *rt);
int			ft_error_exit(const char *msg);

#endif
