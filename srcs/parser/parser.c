/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 18:01:33 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/29 12:35:18 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static int	ft_dispatch(t_scene *scene, char **tok)
{
	static const t_dispatch	table[] = {
	{"A", ft_parse_ambient},
	{"C", ft_parse_camera},
	{"L", ft_parse_light},
	{"sp", ft_parse_sphere},
	{"pl", ft_parse_plane},
	{"cy", ft_parse_cylinder},
	{NULL, NULL}
	};
	int						i;
	int						ret;

	i = 0;
	while (table[i].id != NULL)
	{
		if (ft_strcmp(tok[0], table[i].id) == 0)
		{
			ret = table[i].fn(scene, tok);
			return (ret);
		}
		i++;
	}
	ft_error_exit("unknown identifier");
	return (1);
}

static int	ft_parse_line(t_scene *scene, char *line)
{
	char	**tok;
	int		ret;

	tok = ft_split_ws(line);
	if (!tok)
		return (1);
	if (!tok[0])
	{
		ft_freeptr((void **)tok);
		return (0);
	}
	ret = ft_dispatch(scene, tok);
	ft_freeptr((void **)tok);
	return (ret);
}

static int	ft_parse_loop(t_scene *scene, int fd)
{
	char	*line;
	int		ret;

	line = get_next_line(fd);
	while (line != NULL)
	{
		ret = ft_parse_line(scene, line);
		free(line);
		if (ret != 0)
			return (1);
		line = get_next_line(fd);
	}
	return (0);
}

int	ft_parse_scene(t_rt *rt, const char *path)
{
	int	fd;
	int	ret;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_error_exit("cannot open scene file");
		return (1);
	}
	ret = ft_parse_loop(&rt->scene, fd);
	close(fd);
	get_next_line(-1); //Free static if there was an error in parse_loop;
	if (ret != 0)
		return (1);
	ret = ft_check_scene(&rt->scene);
	return (ret);
}
