/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 21:16:40 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/08 21:45:41 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/* Creates a new min-heap priority queue. */
int	ft_heap_new(t_heap *heap, int capacity)
{
	heap->coder_ids = (int *)malloc(capacity * sizeof(int));
	if (!heap->coder_ids)
		return (0);
	heap->keys = (long *)malloc(capacity * sizeof(long));
	if (!heap->keys)
		return (free(heap->coder_ids), 0);
	heap->size = 0;
	heap->capacity = capacity;
	return (1);
}

/* Adds a new element to the heap and re-sorts the heap. */
int	ft_heappush(t_heap *heap, int coder_id, long key)
{
	int	current;

	if (heap->size >= heap->capacity)
		return (0);
	current = heap->size;
	heap->coder_ids[current] = coder_id;
	heap->keys[current] = key;
	heap->size++;
	bubble_up(heap, current);
	return (1);
}

int	ft_heappop(t_heap *heap, int *coder_id)
{
	if (heap->size == 0)
		return (0);
	*coder_id = heap->coder_ids[0];
	heap->size--;
	if (heap->size > 0)
	{
		heap->coder_ids[0] = heap->coder_ids[heap->size];
		heap->keys[0] = heap->keys[heap->size];
		bubble_down(heap);
	}
	return (1);
}

int	ft_heappeek(t_heap *heap)
{
	if (heap->size == 0)
		return (-1);
	return (heap->coder_ids[0]);
}

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