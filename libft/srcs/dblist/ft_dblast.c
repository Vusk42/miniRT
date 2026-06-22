/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:35:17 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 16:57:13 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/data/dblist.h"

t_stack	*ft_dblast(t_stack *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}
