/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:34:32 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 13:54:58 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/data/tree.h"

void	btree_insert_data(t_btree **root,
		void *content, int (*cmpf)(void *, void *))
{
	t_btree	*btree;

	if (!root || !(*root) || !content)
	{
		if (content && root)
			*root = btree_create_node(content);
		return ;
	}
	btree = *root;
	if ((*cmpf)(content, (*root)->content) < 0)
	{
		if (btree->left)
			btree_insert_data(&btree->left, content, cmpf);
		else
			btree->left = btree_create_node(content);
	}
	else
	{
		if (btree->right)
			btree_insert_data(&btree->right, content, cmpf);
		else
			btree->right = btree_create_node(content);
	}
}
