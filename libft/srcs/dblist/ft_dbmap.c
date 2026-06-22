/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:36:19 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 16:57:19 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/data/dblist.h"

t_stack	*ft_dbmap(t_stack *stack, void *(*f)(void *), void (*del)(void *))
{
	t_stack	*newl;
	t_stack	*node;
	void	*data;

	if (!stack || !f || !del)
		return (NULL);
	node = NULL;
	newl = NULL;
	data = NULL;
	while (stack)
	{
		data = f(stack->content);
		node = ft_dbnew(data);
		if (!node)
		{
			del(data);
			ft_dbclear(&newl, del);
			return (NULL);
		}
		ft_dbadd_back(&newl, node);
		stack = stack->next;
	}
	return (newl);
}
