/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 12:06:02 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/23 23:21:34 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	ft_check_args(int ac, char **av)
{
	size_t	len;

	if (ac != 2)
	{
		ft_error_exit("usage: ./miniRT <scene.rt>");
		return (1);
	}
	len = ft_strlen(av[1]);
	if (len < 4 || ft_strncmp(av[1] + len - 3, ".rt", 4) != 0)
	{
		ft_error_exit("scene file must have a .rt extension");
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_rt	rt;

	if (ft_check_args(ac, av) != 0)
		return (1);
	ft_bzero(&rt, sizeof(t_rt));
	if (ft_parse_scene(&rt, av[1]) != 0)
	{
		ft_cleanup(&rt);
		return (1);
	}
	if (ft_init_window(&rt) != 0)
	{
		ft_cleanup(&rt);
		return (1);
	}
	ft_render(&rt);
	mlx_loop(rt.mlx);
	ft_cleanup(&rt);
	return (0);
}
