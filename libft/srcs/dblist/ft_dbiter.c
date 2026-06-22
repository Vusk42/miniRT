/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:34:07 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 16:57:07 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/data/dblist.h"

void	ft_dbiter(t_stack *stack, void (*f)(void *))
{
	if (!stack || !f)
		return ;
	while (stack)
	{
		f(stack->content);
		stack = stack->next;
	}
}
