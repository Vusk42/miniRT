/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_world.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 17:25:15 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/28 18:52:47 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_parse_ambient(t_scene *scene, char **tok)
{
	if (ft_tab_len(tok) != 3)
	{
		ft_error_exit("A: usage 'A ratio R,G,B'");
		return (1);
	}
	if (scene->has_ambient != 0)
	{
		ft_error_exit("A defined more than once");
		return (1);
	}
	if (ft_parse_double(tok[1], &scene->ambient.ratio)
		|| ft_out_range(scene->ambient.ratio, 0.0, 1.0))
	{
		ft_error_exit("A: ratio must be in [0,1]");
		return (1);
	}
	if (ft_parse_color(tok[2], &scene->ambient.color))
	{
		ft_error_exit("A: invalid color R,G,B");
		return (1);
	}
	scene->has_ambient = 1;
	return (0);
}

static int	ft_fill_camera(t_scene *scene, char **tok)
{
	if (ft_parse_vec3(tok[1], &scene->camera.pos))
	{
		ft_error_exit("C: invalid position");
		return (1);
	}
	if (ft_parse_norm(tok[2], &scene->camera.dir))
	{
		ft_error_exit("C: invalid orientation");
		return (1);
	}
	if (ft_parse_double(tok[3], &scene->camera.fov)
		|| ft_out_range(scene->camera.fov, 0.0, 180.0))
	{
		ft_error_exit("C: fov must be in [0,180]");
		return (1);
	}
	return (0);
}

int	ft_parse_camera(t_scene *scene, char **tok)
{
	if (ft_tab_len(tok) != 4)
	{
		ft_error_exit("C: usage 'C pos dir fov'");
		return (1);
	}
	if (scene->has_camera != 0)
	{
		ft_error_exit("C defined more than once");
		return (1);
	}
	if (ft_fill_camera(scene, tok))
		return (1);
	scene->has_camera = 1;
	return (0);
}

static int	ft_fill_light(t_scene *scene, char **tok)
{
	if (ft_parse_vec3(tok[1], &scene->light.pos))
	{
		ft_error_exit("L: invalid position");
		return (1);
	}
	if (ft_parse_double(tok[2], &scene->light.ratio)
		|| ft_out_range(scene->light.ratio, 0.0, 1.0))
	{
		ft_error_exit("L: ratio must be in [0,1]");
		return (1);
	}
	if (ft_parse_color(tok[3], &scene->light.color))
	{
		ft_error_exit("L: invalid color R,G,B");
		return (1);
	}
	return (0);
}

int	ft_parse_light(t_scene *scene, char **tok)
{
	if (ft_tab_len(tok) != 4)
	{
		ft_error_exit("L: usage 'L pos ratio R,G,B'");
		return (1);
	}
	if (scene->has_light != 0)
	{
		ft_error_exit("L defined more than once");
		return (1);
	}
	if (ft_fill_light(scene, tok))
		return (1);
	scene->has_light = 1;
	return (0);
}
