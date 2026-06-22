/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 21:20:03 by marudlof          #+#    #+#             */
/*   Updated: 2025/10/20 22:59:28 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

int				ft_sqrt(int nb);
int				ft_power(int nb, int power);
int				ft_nextprime(int nb);
int				ft_isprime(int nb);
int				ft_fibonacci(int index);
int				ft_factorial(int nb);

long long int	ft_abs(long long int nb);

#endif
