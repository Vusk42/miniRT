/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 23:16:46 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/23 23:17:11 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(rt->mlx);
}

void	ft_close_hook(void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	mlx_close_window(rt->mlx);
}
