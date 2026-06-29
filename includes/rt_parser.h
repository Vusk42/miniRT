/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 18:20:51 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/28 19:14:33 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_PARSER_H
# define RT_PARSER_H

# include "rt_types.h"

typedef int	(*t_parse_fn)(t_scene *scene, char **tok);

typedef struct s_dispatch
{
	const char	*id;
	t_parse_fn	fn;
}	t_dispatch;

int			ft_parse_scene(t_rt *rt, const char *path);
int			ft_parse_ambient(t_scene *scene, char **tok);
int			ft_parse_camera(t_scene *scene, char **tok);
int			ft_parse_light(t_scene *scene, char **tok);
int			ft_parse_sphere(t_scene *scene, char **tok);
int			ft_parse_plane(t_scene *scene, char **tok);
int			ft_parse_cylinder(t_scene *scene, char **tok);

int			ft_parse_double(const char *s, double *out);
int			ft_parse_vec3(const char *s, t_vec3 *out);
int			ft_parse_color(const char *s, t_color *out);
int			ft_parse_norm(const char *s, t_vec3 *out);

char		**ft_split_ws(const char *s);
int			ft_tab_len(char **tab);
int			ft_out_range(double v, double lo, double hi);
int			ft_check_scene(t_scene *scene);

#endif
