/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:35:36 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 17:04:10 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/ft/data/tree.h"

void	*btree_search_item(t_btree *root,
			void *data_ref, int (*cmpf)(void *, void *))
{
	void	*res;

	res = NULL;
	if (!root)
		return (NULL);
	res = btree_search_item(root->left, data_ref, cmpf);
	if (res)
		return (res);
	if (cmpf(root->content, data_ref) == 0)
		return (root);
	return (btree_search_item(root->right, data_ref, cmpf));
}
