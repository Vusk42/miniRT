/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 23:15:19 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:02:06 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <unistd.h>

/**
 * @brief Print "Error" followed by an explanatory message on stderr.
 * @param msg Message to display, or NULL to print only "Error".
 * @return Always 1, so callers can `return (ft_error_exit(...))`.
 */
int	ft_error_exit(const char *msg)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	if (msg != NULL)
		ft_putendl_fd((char *)msg, STDERR_FILENO);
	return (1);
}

/**
 * @brief Release every resource held by the program (objects list, MLX).
 * @param rt Main program context to clean up.
 */
void	ft_cleanup(t_rt *rt)
{
	if (rt->scene.objects != NULL)
		ft_lstclear(&rt->scene.objects, free);
	if (rt->mlx != NULL)
		mlx_terminate(rt->mlx);
}
