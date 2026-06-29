/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:08:54 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/29 12:31:32 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
