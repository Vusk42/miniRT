/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 23:16:46 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:02:11 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Keyboard callback: close the window when ESC is pressed.
 * @param keydata Key event data provided by MLX42.
 * @param param Opaque pointer to the t_rt context.
 */
void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(rt->mlx);
}

/**
 * @brief Window-close callback: close the window (e.g. red cross clicked).
 * @param param Opaque pointer to the t_rt context.
 */
void	ft_close_hook(void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	mlx_close_window(rt->mlx);
}
