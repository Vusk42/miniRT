/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:12:46 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/28 18:03:21 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

int	ft_out_range(double v, double lo, double hi)
{
	if (v < lo || v > hi)
		return (1);
	return (0);
}

int	ft_check_scene(t_scene *scene)
{
	if (scene->has_ambient == 0)
	{
		ft_error_exit("scene: missing ambient (A)");
		return (1);
	}
	if (scene->has_camera == 0)
	{
		ft_error_exit("scene: missing camera (C)");
		return (1);
	}
	if (scene->has_light == 0)
	{
		ft_error_exit("scene: missing light (L)");
		return (1);
	}
	return (0);
}
