/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dblist.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:02:35 by marudlof          #+#    #+#             */
/*   Updated: 2025/10/30 20:16:13 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DBLIST_H
# define DBLIST_H

# include <stddef.h>

typedef struct s_content
{
	int		value;
	int		index;
}				t_content;

typedef struct s_stack
{
	void				*content;
	struct s_stack		*prev;
	struct s_stack		*next;
}				t_stack;

void	ft_dbadd_back(t_stack **stack, t_stack *newl);
void	ft_dbadd_front(t_stack **stack, t_stack *newl);
void	ft_dbclear(t_stack **stack, void (*del)(void*));
void	ft_dbdelone(t_stack *stack, void (*del)(void*));
void	ft_dbiter(t_stack *stack, void (*f)(void *));
t_stack	*ft_dblast(t_stack *stack);
t_stack	*ft_dbmap(t_stack *stack, void *(*f)(void *), void (*del)(void *));
t_stack	*ft_dbnew(void *content);
int		ft_dbsize(t_stack *stack);
#endif
