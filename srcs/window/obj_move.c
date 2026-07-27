/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 19:32:20 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 19:36:59 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Address of an object's position field, whatever its type.
 * @param obj Object (sphere center, plane point or cylinder center).
 * @return A pointer to the position vector, editable in place.
 */
static t_vec3	*ft_obj_pos(t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		return (&obj->shape.sp.center);
	if (obj->type == OBJ_PLANE)
		return (&obj->shape.pl.point);
	return (&obj->shape.cy.center);
}

/**
 * @brief Translate the selected object along the world axes.
 *
 * J/L move along X, I/K along Y and U/O along Z, each by OBJ_MOVE_STEP.
 * @param obj Object whose position is updated in place.
 * @param key MLX42 key symbol of the pressed key.
 * @return 1 if the key mapped to a translation, 0 otherwise.
 */
int	ft_obj_move(t_object *obj, int key)
{
	t_vec3	*p;

	p = ft_obj_pos(obj);
	if (key == MLX_KEY_L)
		p->x += OBJ_MOVE_STEP;
	else if (key == MLX_KEY_J)
		p->x -= OBJ_MOVE_STEP;
	else if (key == MLX_KEY_I)
		p->y += OBJ_MOVE_STEP;
	else if (key == MLX_KEY_K)
		p->y -= OBJ_MOVE_STEP;
	else if (key == MLX_KEY_O)
		p->z += OBJ_MOVE_STEP;
	else if (key == MLX_KEY_U)
		p->z -= OBJ_MOVE_STEP;
	else
		return (0);
	return (1);
}

/**
 * @brief Cycle the selected object to the next one in the scene list.
 *
 * Wraps back to the first object after the last one.
 * @param scene Scene holding the object list and the current selection.
 * @return 1 so the caller re-renders (the highlight moves).
 */
int	ft_select_next(t_scene *scene)
{
	t_list	*node;

	node = scene->objects;
	while (node != NULL && node->content != scene->selected)
		node = node->next;
	if (node != NULL && node->next != NULL)
		scene->selected = node->next->content;
	else if (scene->objects != NULL)
		scene->selected = scene->objects->content;
	return (1);
}
