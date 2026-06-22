/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:28:12 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 16:57:45 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/data/list.h"

void	ft_lstadd_back(t_list **lst, t_list *newl)
{
	t_list	*tmp;

	if (!lst || !newl)
		return ;
	if (!(*lst))
	{
		*lst = newl;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newl;
}
