/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_level_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:35:16 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 13:53:10 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft/data/tree.h"

static int	max(int a, int b)
{
	if (a < b)
		return (b);
	else
		return (a);
}

int	btree_level_count(t_btree *root)
{
	if (!root)
		return (0);
	return (max(btree_level_count(root->left),
			btree_level_count(root->right)) + 1);
}
