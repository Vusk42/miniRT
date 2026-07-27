/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 12:06:02 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/28 00:18:48 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Validate the command-line arguments.
 * @param ac Argument count.
 * @param av Argument vector.
 * @return 0 if exactly one argument with a ".rt" extension is given,
 * 1 otherwise (an error message is printed).
 */
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

/**
 * @brief Program entry point: parse the scene, open the window and render it.
 * @param ac Argument count.
 * @param av Argument vector (expects av[1] = path to a .rt scene).
 * @return 0 on success, 1 on any error (args, parsing or window init).
 */
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
	if (rt.scene.objects != NULL)
		rt.scene.selected = rt.scene.objects->content;
	ft_render(&rt, 1);
	mlx_loop(rt.mlx);
	ft_cleanup(&rt);
	return (0);
}
