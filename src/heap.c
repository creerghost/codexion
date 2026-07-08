/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 21:16:40 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/09 00:28:45 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/**
 * Creates a new min-heap priority queue.
 * 
 * heap: Pointer to the heap structure to initialize.
 * capacity: Maximum number of elements the heap can hold.
 * Returns true if successful, false on allocation failure.
 */
bool	ft_heap_new(t_heap *heap, int capacity)
{
	heap->coder_ids = (int *)ft_calloc(capacity * sizeof(int));
	if (!heap->coder_ids)
		return (false);
	heap->keys = (long *)ft_calloc(capacity * sizeof(long));
	if (!heap->keys)
		return (free(heap->coder_ids), false);
	heap->size = 0;
	heap->capacity = capacity;
	return (true);
}

/**
 * Adds a new element to the heap and re-sorts the heap.
 * 
 * heap: Pointer to the heap structure.
 * coder_id: The coder ID to add.
 * key: The priority key to add.
 * Returns true if the element was added successfully, false if the heap is full.
 */
bool	ft_heappush(t_heap *heap, int coder_id, long key)
{
	int	current;

	if (heap->size >= heap->capacity)
		return (false);
	current = heap->size;
	heap->coder_ids[current] = coder_id;
	heap->keys[current] = key;
	heap->size++;
	bubble_up(heap, current);
	return (true);
}

/**
 * Removes and returns the element with the highest priority (minimum key) 
 * from the heap.
 * 
 * heap: Pointer to the heap structure.
 * coder_id: Pointer to store the coder ID of the removed element.
 * Returns true if an element was removed, false if the heap is empty.
 */
bool	ft_heappop(t_heap *heap, int *coder_id)
{
	if (heap->size == 0)
		return (false);
	*coder_id = heap->coder_ids[0];
	heap->size--;
	if (heap->size > 0)
	{
		heap->coder_ids[0] = heap->coder_ids[heap->size];
		heap->keys[0] = heap->keys[heap->size];
		bubble_down(heap);
	}
	return (true);
}

/**
 * Returns the element with the highest priority (minimum key) without removing it.
 * 
 * heap: Pointer to the heap structure.
 * Returns the coder ID of the element with the highest priority, or -1 if the heap is empty.
 */
int	ft_heappeek(t_heap *heap)
{
	if (heap->size == 0)
		return (-1);
	return (heap->coder_ids[0]);
}

/**
 * Frees the memory used by the heap.
 * 
 * heap: Pointer to the heap structure.
 */
void	ft_heapfree(t_heap *heap)
{
	if (heap->coder_ids)
		free(heap->coder_ids);
	if (heap->keys)
		free(heap->keys);
	heap->coder_ids = NULL;
	heap->keys = NULL;
	heap->size = 0;
	heap->capacity = 0;
}