/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 13:40:27 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:14:48 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RENDER_H
# define RT_RENDER_H

# include "rt_types.h"

# define RT_MAX_DIST 1e30
# define RT_EPSILON 1e-4
# define RT_EPSILON_PARALLEL 1e-6
# define RT_EPSILON_CAP 1e-3

int			ft_init_window(t_rt *rt);
void		ft_render(t_rt *rt);
void		ft_setup_camera(t_camera *cam);
t_ray		ft_primary_ray(const t_camera *cam, uint32_t x, uint32_t y);
double		ft_hit_sphere(const t_sphere *sp, t_ray ray);
double		ft_hit_plane(const t_plane *pl, t_ray ray);
double		ft_hit_cylinder(const t_cylinder *cy, t_ray ray);
double		ft_hit_object(const t_object *obj, t_ray ray);
t_vec3		ft_object_normal(const t_object *obj, t_vec3 point);
int			ft_closest_hit(t_scene *scene, t_ray ray, t_hit *hit);
t_color		ft_lighting(t_scene *scene, t_hit *hit);
void		ft_key_hook(mlx_key_data_t keydata, void *param);
void		ft_close_hook(void *param);

uint32_t	ft_color_to_int(t_color c);
void		ft_cleanup(t_rt *rt);
int			ft_error_exit(const char *msg);

#endif
