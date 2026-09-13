/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_heap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 15:26:28 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/queue_api.h"
#include "queue_internal.h"

static void	swap_requests(t_request *first, t_request *second)
{
	t_request	tmp;

	tmp = *first;
	*first = *second;
	*second = tmp;
}

static void	heapify_down(t_queue *queue, size_t idx)
{
	size_t	left;
	size_t	right;
	size_t	best;

	while (1)
	{
		left = idx * 2 + 1;
		right = left + 1;
		best = idx;
		if (left < queue->size && request_precedes(
				&queue->heap[left], &queue->heap[best], queue->mode))
			best = left;
		if (right < queue->size && request_precedes(
				&queue->heap[right], &queue->heap[best], queue->mode))
			best = right;
		if (best == idx)
			break ;
		swap_requests(&queue->heap[idx], &queue->heap[best]);
		idx = best;
	}
}

bool	queue_push(t_queue *queue, t_request request)
{
	size_t	idx;
	size_t	parent;

	if (queue == NULL || queue->heap == NULL)
		return (false);
	if (queue->size >= queue->capacity)
		return (false);
	request.sequence = queue->next_sequence++;
	idx = queue->size;
	queue->heap[idx] = request;
	queue->size++;
	while (idx > 0)
	{
		parent = (idx - 1) / 2;
		if (!request_precedes(&queue->heap[idx],
				&queue->heap[parent], queue->mode))
			break ;
		swap_requests(&queue->heap[idx], &queue->heap[parent]);
		idx = parent;
	}
	return (true);
}

bool	queue_pop(t_queue *queue, t_request *request)
{
	size_t	idx;

	if (queue == NULL || request == NULL || queue->size == 0)
		return (false);
	*request = queue->heap[0];
	queue->size--;
	if (queue->size == 0)
		return (true);
	queue->heap[0] = queue->heap[queue->size];
	heapify_down(queue, 0);
	return (true);
}

bool	queue_peek(const t_queue *queue, t_request *request)
{
	if (queue == NULL || request == NULL || queue->size == 0)
		return (false);
	*request = queue->heap[0];
	return (true);
}
