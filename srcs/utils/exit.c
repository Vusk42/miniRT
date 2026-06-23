/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 23:15:19 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/23 23:16:20 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <unistd.h>

int	ft_error_exit(const char *msg)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	if (msg != NULL)
		ft_putendl_fd((char *)msg, STDERR_FILENO);
	return (1);
}

void	ft_cleanup(t_rt *rt)
{
	if (rt->scene.objects != NULL)
		ft_lstclear(&rt->scene.objects, free);
	if (rt->mlx != NULL)
		mlx_terminate(rt->mlx);
}
