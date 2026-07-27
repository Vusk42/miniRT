/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:47:38 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:01:17 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

/**
 * @brief Append a heap-allocated copy of an object to the scene list.
 * @param scene Scene whose object list is extended.
 * @param obj Object to copy and store.
 * @return 0 on success, 1 if allocation fails.
 */
int	ft_add_object(t_scene *scene, t_object *obj)
{
	t_list		*node;
	t_object	*copy;

	copy = malloc(sizeof(t_object));
	if (!copy)
		return (1);
	*copy = *obj;
	node = ft_lstnew(copy);
	if (!node)
	{
		free(copy);
		return (1);
	}
	ft_lstadd_back(&scene->objects, node);
	return (0);
}
