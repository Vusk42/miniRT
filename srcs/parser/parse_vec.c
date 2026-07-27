/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:08:54 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:01:30 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Parse a "x,y,z" triple into a vector.
 * @param s String of three comma-separated numbers.
 * @param out Output vector on success.
 * @return 0 on success, 1 if the format or any component is invalid.
 */
int	ft_parse_vec3(const char *s, t_vec3 *out)
{
	char	**split;
	int		err;

	split = ft_split(s, ',');
	if (!split)
		return (1);
	err = 1;
	if (ft_tab_len(split) == 3)
	{
		err = ft_parse_double(split[0], &out->x);
		err += ft_parse_double(split[1], &out->y);
		err += ft_parse_double(split[2], &out->z);
	}
	ft_freeptr((void **)split);
	return (err != 0);
}

/**
 * @brief Convert three "R,G,B" tokens in [0,255] to a normalized color.
 * @param split Array of exactly three numeric strings.
 * @param out Output color with components normalized to [0,1].
 * @return 0 on success, 1 if a component is invalid or out of [0,255].
 */
static int	ft_fill_color(char **split, t_color *out)
{
	t_vec3	color;

	if (ft_parse_double(split[0], &color.x)
		|| ft_parse_double(split[1], &color.y)
		|| ft_parse_double(split[2], &color.z))
		return (1);
	if (ft_out_range(color.x, 0.0, 255.0)
		|| ft_out_range(color.y, 0.0, 255.0)
		|| ft_out_range(color.z, 0.0, 255.0))
		return (1);
	out->x = color.x / 255.0;
	out->y = color.y / 255.0;
	out->z = color.z / 255.0;
	return (0);
}

/**
 * @brief Parse an "R,G,B" string into a normalized color.
 * @param s String of three comma-separated integers in [0,255].
 * @param out Output color with components normalized to [0,1].
 * @return 0 on success, 1 if the format or any component is invalid.
 */
int	ft_parse_color(const char *s, t_color *out)
{
	char	**split;
	int		err;

	split = ft_split(s, ',');
	if (!split)
		return (1);
	err = 1;
	if (ft_tab_len(split) == 3)
		err = ft_fill_color(split, out);
	ft_freeptr((void **)split);
	return (err);
}

/**
 * @brief Parse an orientation vector with components in [-1,1] and normalize.
 * @param s String of three comma-separated numbers.
 * @param out Output normalized vector on success.
 * @return 0 on success, 1 if invalid, out of range or a zero-length vector.
 */
int	ft_parse_norm(const char *s, t_vec3 *out)
{
	t_vec3	v;

	if (ft_parse_vec3(s, &v) != 0)
		return (1);
	if (ft_out_range(v.x, -1.0, 1.0)
		|| ft_out_range(v.y, -1.0, 1.0)
		|| ft_out_range(v.z, -1.0, 1.0))
		return (1);
	if (vec_len2(v) == 0.0)
		return (1);
	*out = vec_normalize(v);
	return (0);
}
