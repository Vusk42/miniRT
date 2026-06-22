/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:28:37 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 16:57:50 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/data/list.h"

void	ft_lstadd_front(t_list **lst, t_list *newl)
{
	if (!lst || !newl)
		return ;
	newl->next = *lst;
	*lst = newl;
}
