/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 16:48:00 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/22 17:01:46 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBVEC_H
# define LIBVEC_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

t_vec3	vec_new(double x, double y, double z);
t_vec3	vec_add(t_vec3 a, t_vec3 b);
t_vec3	vec_sub(t_vec3 a, t_vec3 b);
t_vec3	vec_scale(t_vec3 v, double t);
t_vec3	vec_neg(t_vec3 v);

double	vec_dot(t_vec3 a, t_vec3 b);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);
t_vec3	vec_mul(t_vec3 a, t_vec3 b);

double	vec_len(t_vec3 v);
double	vec_len2(t_vec3 v);
t_vec3	vec_normalize(t_vec3 v);
double	vec_dist(t_vec3 a, t_vec3 b);

t_vec3	vec_reflect(t_vec3 v, t_vec3 n);
t_vec3	vec_lerp(t_vec3 a, t_vec3 b, double t);
t_vec3	vec_clamp(t_vec3 v, double lo, double hi);

#endif
