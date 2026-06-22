/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:44:50 by marudlof          #+#    #+#             */
/*   Updated: 2026/04/29 22:59:11 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H

# include <stdlib.h>
# include <stddef.h>

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);

int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
char	*ft_itoa(int n);

char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);

size_t	ft_strlen(const char *str);
size_t	ft_nbrlen_base(long long int n, size_t base);
size_t	ft_unbrlen_base(unsigned long long int n, size_t base);
size_t	ft_tabsize(void **tab);

size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, char const *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);

char	*ft_strnstr(const char *big, const char *little, size_t len);

void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);

char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

int		ft_tolower(int c);
int		ft_toupper(int c);

#endif
