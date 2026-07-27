/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_world.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 17:25:15 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:01:33 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Parse an ambient light line: `A ratio R,G,B`.
 * @param scene Scene receiving the ambient light (only one allowed).
 * @param tok NULL-terminated tokens for the line.
 * @return 0 on success, 1 on a format, range or duplicate error.
 */
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

/**
 * @brief Parse and store the camera fields (position, orientation, FOV).
 * @param scene Scene receiving the camera.
 * @param tok NULL-terminated tokens for the line.
 * @return 0 on success, 1 on an invalid field or out-of-range FOV.
 */
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

/**
 * @brief Parse a camera line: `C pos dir fov`.
 * @param scene Scene receiving the camera (only one allowed).
 * @param tok NULL-terminated tokens for the line.
 * @return 0 on success, 1 on a format or duplicate error.
 */
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

/**
 * @brief Parse and store the light fields (position, brightness, color).
 * @param scene Scene receiving the light.
 * @param tok NULL-terminated tokens for the line.
 * @return 0 on success, 1 on an invalid field or out-of-range brightness.
 */
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

/**
 * @brief Parse a light line: `L pos ratio R,G,B`.
 * @param scene Scene receiving the light (only one allowed).
 * @param tok NULL-terminated tokens for the line.
 * @return 0 on success, 1 on a format or duplicate error.
 */
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
