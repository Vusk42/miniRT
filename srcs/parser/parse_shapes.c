/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 13:53:34 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/28 12:00:00 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Parse and store the sphere fields (center, radius, color).
 * @param obj Object of type OBJ_SPHERE to fill.
 * @param tok NULL-terminated tokens for the line.
 * @return 0 on success, 1 on an invalid field or non-positive diameter.
 */
static int	ft_fill_sphere(t_object *obj, char **tok)
{
	double	diameter;

	if (ft_parse_vec3(tok[1], &obj->shape.sp.center))
	{
		ft_error_exit("sp: invalid center");
		return (1);
	}
	if (ft_parse_double(tok[2], &diameter) || diameter <= 0.0)
	{
		ft_error_exit("sp: diameter must be > 0");
		return (1);
	}
	obj->shape.sp.radius = diameter / 2.0;
	if (ft_parse_color(tok[3], &obj->color))
	{
		ft_error_exit("sp: invalid color R,G,B");
		return (1);
	}
	return (0);
}

/**
 * @brief Parse a sphere line: `sp center diameter R,G,B`.
 * @param scene Scene receiving the sphere.
 * @param tok NULL-terminated tokens for the line.
 * @return 0 on success, 1 on a format, range or allocation error.
 */
int	ft_parse_sphere(t_scene *scene, char **tok)
{
	t_object	obj;

	if (ft_tab_len(tok) != 4)
	{
		ft_error_exit("sp: usage 'sp center diameter R,G,B'");
		return (1);
	}
	obj.type = OBJ_SPHERE;
	if (ft_fill_sphere(&obj, tok))
		return (1);
	if (ft_add_object(scene, &obj))
	{
		ft_error_exit("sp: allocation failed");
		return (1);
	}
	return (0);
}

/**
 * @brief Parse and store the plane fields (point, normal, color).
 * @param obj Object of type OBJ_PLANE to fill.
 * @param tok NULL-terminated tokens for the line.
 * @return 0 on success, 1 on an invalid field.
 */
static int	ft_fill_plane(t_object *obj, char **tok)
{
	if (ft_parse_vec3(tok[1], &obj->shape.pl.point))
	{
		ft_error_exit("pl: invalid point");
		return (1);
	}
	if (ft_parse_norm(tok[2], &obj->shape.pl.normal))
	{
		ft_error_exit("pl: invalid normal");
		return (1);
	}
	if (ft_parse_color(tok[3], &obj->color))
	{
		ft_error_exit("pl: invalid color R,G,B");
		return (1);
	}
	return (0);
}

/**
 * @brief Parse a plane line: `pl point normal R,G,B`.
 * @param scene Scene receiving the plane.
 * @param tok NULL-terminated tokens for the line.
 * @return 0 on success, 1 on a format, range or allocation error.
 */
int	ft_parse_plane(t_scene *scene, char **tok)
{
	t_object	obj;

	if (ft_tab_len(tok) != 4)
	{
		ft_error_exit("pl: usage 'pl point normal R,G,B'");
		return (1);
	}
	obj.type = OBJ_PLANE;
	if (ft_fill_plane(&obj, tok))
		return (1);
	if (ft_add_object(scene, &obj))
	{
		ft_error_exit("pl: allocation failed");
		return (1);
	}
	return (0);
}
