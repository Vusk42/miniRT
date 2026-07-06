/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 13:53:34 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/06 15:02:01 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_parse_sphere(t_scene *scene, char **tok)
{
	t_object	obj;
	double		diameter;

	if (ft_tab_len(tok) != 4)
	{
		ft_error_exit("sp: usage 'sp center diameter R,G,B'");
		return (1);
	}
	obj.type = OBJ_SPHERE;
	if (ft_parse_vec3(tok[1], &obj.shape.sp.center))
	{
		ft_error_exit("sp: invalid center");
		return (1);
	}
	if (ft_parse_double(tok[2], &diameter) || diameter <= 0.0)
	{
		ft_error_exit("sp: diameter must be > 0");
		return (1);
	}
	obj.shape.sp.radius = diameter / 2.0;
	if (ft_parse_color(tok[3], &obj.color))
	{
		ft_error_exit("sp: invalid color R,G,B");
		return (1);
	}
	if (ft_add_object(scene, &obj))
	{
		ft_error_exit("sp: allocation failed");
		return (1);
	}
	return (0);
}

int	ft_parse_plane(t_scene *scene, char **tok)
{
	t_object	obj;

	if (ft_tab_len(tok) != 4)
	{
		ft_error_exit("pl: usage 'pl point normal R,G,B'");
		return (1);
	}
	obj.type = OBJ_PLANE;
	if (ft_parse_vec3(tok[1], &obj.shape.pl.point))
	{
		ft_error_exit("pl: invalid point");
		return (1);
	}
	if (ft_parse_norm(tok[2], &obj.shape.pl.normal))
	{
		ft_error_exit("pl: invalid normal");
		return (1);
	}
	if (ft_parse_color(tok[3], &obj.color))
	{
		ft_error_exit("pl: invalid color R,G,B");
		return (1);
	}
	if (ft_add_object(scene, &obj))
	{
		ft_error_exit("pl: allocation failed");
		return (1);
	}
	return (0);
}

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
	if (ft_parse_color(tok[5], &obj->color))
	{
		ft_error_exit("cy: invalid color R,G,B");
		return (1);
	}
	return (0);
}

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
	if (ft_add_object(scene, &obj))
	{
		ft_error_exit("cy: allocation failed");
		return (1);
	}
	return (0);
}
