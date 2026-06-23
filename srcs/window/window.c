/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 23:17:25 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/23 23:20:21 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_init_window(t_rt *rt)
{
	
	rt->mlx = mlx_init(WIN_W, WIN_H, WIN_TITLE, false);
	if (rt->mlx == NULL)
	{
		ft_error_exit(mlx_strerror(mlx_errno));
		return (1);
	}
	rt->img = mlx_new_image(rt->mlx, WIN_W, WIN_H);
	if (rt->img == NULL)
	{
		ft_error_exit(mlx_strerror(mlx_errno));
		return (1);
	}
	if (mlx_image_to_window(rt->mlx, rt->img, 0, 0) < 0)
	{
		ft_error_exit(mlx_strerror(mlx_errno));
		return (1);
	}
	mlx_key_hook(rt->mlx, &ft_key_hook, rt);
	mlx_close_hook(rt->mlx, &ft_close_hook, rt);
	return (0);
}
