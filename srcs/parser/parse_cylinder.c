/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 00:36:42 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/28 00:41:07 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Parse and store the cylinder geometry (center, axis, radius, height).
 * @param obj Object of type OBJ_CYLINDER to fill.
 * @param tok NULL-terminated tokens for the line.
 * @return 0 on success, 1 on an invalid field or non-positive size.
 */
static int	ft_fill_cylinder(t_object *obj, char **tok)
{
	if (ft_parse_vec3(tok[1], &obj->shape.cy.center))
	{
		ft_error_exit("cy: invalid center");
		return (1);
	}
	if (ft_parse_norm(tok[2], &obj->shape.cy.axis))
	{
		ft_error_exit("cy: invalid axis");
		return (1);
	}
	if (ft_parse_double(tok[3], &obj->shape.cy.radius)
		|| obj->shape.cy.radius <= 0.0)
	{
		ft_error_exit("cy: diameter must be > 0");
		return (1);
	}
	obj->shape.cy.radius /= 2.0;
	if (ft_parse_double(tok[4], &obj->shape.cy.height)
		|| obj->shape.cy.height <= 0.0)
	{
		ft_error_exit("cy: height must be > 0");
		return (1);
	}
	return (0);
}

/**
 * @brief Parse a cylinder line: `cy center axis diam height R,G,B`.
 * @param scene Scene receiving the cylinder.
 * @param tok NULL-terminated tokens for the line.
 * @return 0 on success, 1 on a format, range or allocation error.
 */
int	ft_parse_cylinder(t_scene *scene, char **tok)
{
	t_object	obj;

	if (ft_tab_len(tok) != 6)
	{
		ft_error_exit("cy: usage 'cy center axis diam height R,G,B'");
		return (1);
	}
	obj.type = OBJ_CYLINDER;
	if (ft_fill_cylinder(&obj, tok))
		return (1);
	if (ft_parse_color(tok[5], &obj.color))
	{
		ft_error_exit("cy: invalid color R,G,B");
		return (1);
	}
	if (ft_add_object(scene, &obj))
	{
		ft_error_exit("cy: allocation failed");
		return (1);
	}
	return (0);
}
