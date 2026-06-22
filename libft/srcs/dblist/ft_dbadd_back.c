/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbadd_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:13:58 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 16:56:32 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/data/dblist.h"

void	ft_dbadd_back(t_stack **stack, t_stack *newl)
{
	t_stack	*tmp;

	if (!stack || !newl)
		return ;
	if (!(*stack))
	{
		*stack = newl;
		return ;
	}
	tmp = *stack;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newl;
	newl->prev = tmp;
}
