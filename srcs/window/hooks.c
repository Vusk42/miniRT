/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 23:16:46 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/28 00:19:06 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Keyboard callback: close on ESC, otherwise edit the scene.
 *
 * Keys are dispatched by ft_handle_key (camera, selection and object edits)
 * and trigger a draft re-render on press and while held (repeat), so that
 * editing stays responsive; the full quality pass is left to ft_loop_hook.
 * Release events are ignored.
 * @param keydata Key event data provided by MLX42.
 * @param param Opaque pointer to the t_rt context.
 */
void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(rt->mlx);
		return ;
	}
	if (keydata.action == MLX_RELEASE)
	{
		if (rt->held > 0)
			rt->held--;
		return ;
	}
	if (keydata.action == MLX_PRESS)
		rt->held++;
	if (ft_handle_key(rt, keydata.key))
	{
		ft_render(rt, RT_DRAFT_STEP);
		rt->last_edit = mlx_get_time();
		rt->pending = 1;
	}
}

/**
 * @brief Per-frame callback: re-render at full quality once editing settles.
 *
 * Refines RT_REFINE_DELAY seconds after the last scene change, but only once
 * every key is released: a held key would otherwise trigger a costly full
 * pass during the gap before the keyboard auto-repeat kicks in. The
 * RT_REFINE_MAX fallback keeps a missed release event from freezing the
 * image at draft quality forever.
 * @param param Opaque pointer to the t_rt context.
 */
void	ft_loop_hook(void *param)
{
	t_rt	*rt;
	double	idle;

	rt = (t_rt *)param;
	if (rt->pending == 0)
		return ;
	idle = mlx_get_time() - rt->last_edit;
	if (idle < RT_REFINE_MAX && (rt->held > 0 || idle < RT_REFINE_DELAY))
		return ;
	ft_render(rt, 1);
	rt->pending = 0;
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
