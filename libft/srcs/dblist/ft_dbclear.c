/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbclear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:27:58 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 16:56:54 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/ft/data/dblist.h"

void	ft_dbclear(t_stack **stack, void (*del)(void *))
{
	if (!stack || !del || !(*stack))
		return ;
	ft_dbclear(&(*stack)->next, del);
	(del)((*stack)->content);
	free(*stack);
	*stack = NULL;
}
