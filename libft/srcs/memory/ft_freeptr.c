/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:56:32 by marudlof          #+#    #+#             */
/*   Updated: 2026/05/05 19:22:25 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/ft/memory.h"

void	ft_freeptr(void **nptr)
{
	void	**tmp;

	if (!nptr)
		return ;
	tmp = nptr;
	while (*tmp)
	{
		free(*tmp);
		*tmp = NULL;
		tmp++;
	}
	free(nptr);
	nptr = NULL;
}
