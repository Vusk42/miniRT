/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 19:36:06 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 19:37:11 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Address of an object's orientation axis, or NULL when it has none.
 * @param obj Object (plane normal or cylinder axis; spheres have none).
 * @return A pointer to the axis vector, or NULL for a sphere.
 */
static t_vec3	*ft_obj_axis(t_object *obj)
{
	if (obj->type == OBJ_PLANE)
		return (&obj->shape.pl.normal);
	if (obj->type == OBJ_CYLINDER)
		return (&obj->shape.cy.axis);
	return (NULL);
}

/**
 * @brief Resize a cylinder's height with the '.' and ',' keys.
 * @param obj Object; ignored unless it is a cylinder.
 * @param key MLX42 key symbol of the pressed key.
 * @return 1 if the height changed, 0 otherwise.
 */
static int	ft_resize_height(t_object *obj, int key)
{
	double	d;

	if (obj->type != OBJ_CYLINDER)
		return (0);
	if (key == MLX_KEY_PERIOD)
		d = OBJ_RESIZE_STEP;
	else if (key == MLX_KEY_COMMA)
		d = -OBJ_RESIZE_STEP;
	else
		return (0);
	if (obj->shape.cy.height + d <= RT_EPSILON)
		return (0);
	obj->shape.cy.height += d;
	return (1);
}

/**
 * @brief Rotate a plane normal or cylinder axis around a world axis.
 *
 * Brackets rotate around world X, ';'/'\'' around world Y, each by
 * OBJ_ROT_STEP radians. Spheres cannot be rotated.
 * @param obj Object whose axis is updated in place.
 * @param key MLX42 key symbol of the pressed key.
 * @return 1 if the key mapped to a rotation, 0 otherwise.
 */
int	ft_obj_rotate(t_object *obj, int key)
{
	t_vec3	*ax;

	ax = ft_obj_axis(obj);
	if (ax == NULL)
		return (0);
	if (key == MLX_KEY_LEFT_BRACKET)
		*ax = ft_rotate_axis(*ax, vec_new(1.0, 0.0, 0.0), OBJ_ROT_STEP);
	else if (key == MLX_KEY_RIGHT_BRACKET)
		*ax = ft_rotate_axis(*ax, vec_new(1.0, 0.0, 0.0), -OBJ_ROT_STEP);
	else if (key == MLX_KEY_SEMICOLON)
		*ax = ft_rotate_axis(*ax, vec_new(0.0, 1.0, 0.0), OBJ_ROT_STEP);
	else if (key == MLX_KEY_APOSTROPHE)
		*ax = ft_rotate_axis(*ax, vec_new(0.0, 1.0, 0.0), -OBJ_ROT_STEP);
	else
		return (0);
	*ax = vec_normalize(*ax);
	return (1);
}

/**
 * @brief Resize the selected object (sphere/cylinder radius, cylinder height).
 *
 * '+'/'-' change the radius; '.'/',' change a cylinder's height. A positive
 * lower bound keeps sizes valid.
 * @param obj Object whose size is updated in place.
 * @param key MLX42 key symbol of the pressed key.
 * @return 1 if the key mapped to a resize, 0 otherwise.
 */
int	ft_obj_resize(t_object *obj, int key)
{
	double	d;

	if (key == MLX_KEY_EQUAL || key == MLX_KEY_KP_ADD)
		d = OBJ_RESIZE_STEP;
	else if (key == MLX_KEY_MINUS || key == MLX_KEY_KP_SUBTRACT)
		d = -OBJ_RESIZE_STEP;
	else
		return (ft_resize_height(obj, key));
	if (obj->type == OBJ_SPHERE && obj->shape.sp.radius + d > RT_EPSILON)
		obj->shape.sp.radius += d;
	else if (obj->type == OBJ_CYLINDER && obj->shape.cy.radius + d > RT_EPSILON)
		obj->shape.cy.radius += d;
	else
		return (0);
	return (1);
}
