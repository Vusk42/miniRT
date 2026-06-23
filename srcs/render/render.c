/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 23:15:09 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/23 23:26:35 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_render(t_rt *rt)
{
	uint32_t	x;
	uint32_t	y;
	t_color		c;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			c = vec_new(90, 
				0.1 + 0.4 * ((double)y / WIN_H),
				0.2 + 0.6 * ((double)y / WIN_H));
			mlx_put_pixel(rt->img, x, y, ft_color_to_int(c));
			x++;
		}
		y++;
	}
}
