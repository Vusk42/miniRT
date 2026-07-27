/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 13:18:42 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 19:37:59 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TYPES_H
# define RT_TYPES_H

# include "libft.h"
# include "libvec.h"
# include "MLX42/MLX42.h"

typedef t_vec3	t_color;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	double	fov;
	t_vec3	right;
	t_vec3	up;
}	t_camera;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_light
{
	t_vec3	pos;
	double	ratio;
	t_color	color;
}	t_light;

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_obj_type;

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	axis;
	double	radius;
	double	height;
}	t_cylinder;

typedef struct s_object
{
	t_obj_type	type;
	t_color		color;
	union u_shape
	{
		t_sphere	sp;
		t_plane		pl;
		t_cylinder	cy;
	}	shape;
}	t_object;

typedef struct s_hit
{
	double				t;
	t_vec3				point;
	t_vec3				normal;
	t_color				color;
	const t_object		*obj;
}	t_hit;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_list		*objects;
	t_object	*selected;
	int			has_ambient;
	int			has_camera;
	int			has_light;
}	t_scene;

typedef struct s_rt
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		scene;
}	t_rt;

#endif
