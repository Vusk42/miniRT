/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:30:48 by marudlof          #+#    #+#             */
/*   Updated: 2025/11/17 13:53:33 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/ft/memory.h"
#include "../../includes/ft/data/tree.h"

t_btree	*btree_create_node(void *item)
{
	t_btree	*node;

	node = NULL;
	if (!item)
		return (NULL);
	node = malloc(sizeof(t_btree));
	if (!node)
		return (NULL);
	node->content = malloc(sizeof(void *));
	ft_memcpy(node->content, item, sizeof(void *));
	node->left = NULL;
	node->right = NULL;
	return (node);
}
