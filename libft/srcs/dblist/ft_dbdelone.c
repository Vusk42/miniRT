/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbdelone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:31:51 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 16:57:00 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/ft/data/dblist.h"

void	ft_dbdelone(t_stack *stack, void (*del)(void *))
{
	if (!stack || !del)
		return ;
	(del)(stack->content);
	free(stack);
	stack = NULL;
}
