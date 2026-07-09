/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:54:20 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/08 14:02:20 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** Priority Rules:
** 1. If key[a] < key[b], node `a` has higher priority.
** 2. If keys are equal, lower coder_id has higher priority.
**
** heap: Pointer to the heap structure.
** a: Index of the first node.
** b: Index of the second node.
** Returns true if node `a` has higher priority, false otherwise.
*/
static bool	is_higher_priority(t_heap *heap, int a, int b)
{
	if (heap->keys[a] < heap->keys[b])
		return (true);
	if (heap->keys[a] == heap->keys[b]
		&& heap->coder_ids[a] < heap->coder_ids[b])
		return (true);
	return (false);
}

/**
 * Swaps two nodes in the heap.
 *
 * heap: Pointer to the heap structure.
 * i: Index of the first node to swap.
 * j: Index of the second node to swap.
 */
void	swap_nodes(t_heap *heap, int i, int j)
{
	int		temp_id;
	long	temp_key;

	temp_id = heap->coder_ids[i];
	temp_key = heap->keys[i];
	heap->coder_ids[i] = heap->coder_ids[j];
	heap->keys[i] = heap->keys[j];
	heap->coder_ids[j] = temp_id;
	heap->keys[j] = temp_key;
}

/**
 * Maintains the min-heap property by moving the element at the root
 * down to its correct position.
 *
 * heap: Pointer to the heap structure.
 */
void	bubble_down(t_heap *heap)
{
	int	curr;
	int	sm;
	int	l;
	int	r;

	curr = 0;
	sm = 0;
	l = 1;
	while (l < heap->size)
	{
		r = l + 1;
		if (is_higher_priority(heap, l, curr))
			sm = l;
		if (r < heap->size && is_higher_priority(heap, r, sm))
			sm = r;
		if (sm == curr)
			break ;
		swap_nodes(heap, curr, sm);
		curr = sm;
		l = 2 * curr + 1;
	}
}

/**
 * Maintains the min-heap property by moving the element at the given index
 * up to its correct position.
 *
 * heap: Pointer to the heap structure.
 * current: Index of the element to move up.
 */
void	bubble_up(t_heap *heap, int current)
{
	int	parent;

	parent = (current - 1) / 2;
	while (current > 0 && is_higher_priority(heap, current, parent))
	{
		swap_nodes(heap, current, parent);
		current = parent;
		parent = (current - 1) / 2;
	}
}
