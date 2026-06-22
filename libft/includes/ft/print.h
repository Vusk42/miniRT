/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:42:50 by marudlof          #+#    #+#             */
/*   Updated: 2025/12/01 14:58:16 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include <unistd.h>

int		ft_putchar_fd(const char c, int fd);
int		ft_putendl_fd(const char *s, int fd);
int		ft_putstr_fd(const char *s, int fd);

int		ft_putnbr_fd(int n, int fd);
int		ft_putnbr_base_fd(long long int n, const char *base, int fd);
int		ft_putunbr_base_fd(unsigned long long int n, const char *base, int fd);

int		ft_puthexa_fd(long long int n, const char format, int fd);
int		ft_putuhexa_fd(unsigned long long int n, const char format, int fd);

#endif
