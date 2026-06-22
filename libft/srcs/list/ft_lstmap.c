/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:30:43 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 16:58:57 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/data/list.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newl;
	t_list	*node;
	void	*data;

	if (!lst || !f || !del)
		return (NULL);
	node = NULL;
	newl = NULL;
	data = NULL;
	while (lst)
	{
		data = f(lst->content);
		node = ft_lstnew(data);
		if (!node)
		{
			del(data);
			ft_lstclear(&newl, del);
			return (NULL);
		}
		ft_lstadd_back(&newl, node);
		lst = lst->next;
	}
	return (newl);
}
