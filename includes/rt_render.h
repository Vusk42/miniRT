/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 13:40:27 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/06 15:02:56 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RENDER_H
# define RT_RENDER_H

# include "rt_types.h"

int			ft_init_window(t_rt *rt);
void		ft_render(t_rt *rt);
void		ft_setup_camera(t_camera *cam);
t_ray		ft_primary_ray(const t_camera *cam, uint32_t x, uint32_t y);
void		ft_key_hook(mlx_key_data_t keydata, void *param);
void		ft_close_hook(void *param);

uint32_t	ft_color_to_int(t_color c);
void		ft_cleanup(t_rt *rt);
int			ft_error_exit(const char *msg);

#endif
