/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:12:46 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:01:24 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Count the entries of a NULL-terminated string array.
 * @param tab NULL-terminated array of strings.
 * @return The number of non-NULL entries.
 */
int	ft_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

/**
 * @brief Test whether a value lies outside a closed range.
 * @param v Value to test.
 * @param lo Lower bound (inclusive).
 * @param hi Upper bound (inclusive).
 * @return 1 if v is outside [lo, hi], 0 otherwise.
 */
int	ft_out_range(double v, double lo, double hi)
{
	if (v < lo || v > hi)
		return (1);
	return (0);
}

/**
 * @brief Ensure the mandatory unique elements (A, C, L) are all present.
 * @param scene Fully parsed scene.
 * @return 0 if ambient, camera and light are defined, 1 otherwise.
 */
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
