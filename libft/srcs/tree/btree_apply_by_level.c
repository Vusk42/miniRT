/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_by_level.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaudoin <nbaudoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:27:57 by marudlof          #+#    #+#             */
/*   Updated: 2026/06/17 10:57:00 by nbaudoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/ft/data/tree.h"

void	apply(t_btree *root,
		void (*applyf)(void *item, int current_level,
		int is_first_elem), int level, int *levels)
{
	if (!root)
		return ;
	if (level > *levels)
		return ;
	if (level == *levels)
	{
		applyf(root->content, level, *levels);
		*levels = 0;
		return ;
	}
	apply(root->left, applyf, level + 1, levels);
	apply(root->right, applyf, level + 1, levels);
}

void	btree_apply_by_level(t_btree *root,
		void (*applyf)(void *item, int current_level, int is_first_elem))
{
	int	count;
	int	level;
	int	*levels;

	if (!root)
		return ;
	count = btree_level_count(root);
	levels = malloc(sizeof(int) * count);
	if (!levels)
		return ;
	level = 0;
	while (level < count)
	{
		level++;
		levels[level] = 1;
		apply(root, applyf, 0, &levels[level]);
	}
	free(levels);
}
