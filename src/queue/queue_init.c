/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 14:57:30 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/queue_api.h"
#include <stdlib.h>

void	free_queue(t_queue *queue)
{
	if (queue == NULL)
		return ;
	free(queue->heap);
	queue->heap = NULL;
	queue->size = 0;
	queue->capacity = 0;
	queue->next_sequence = 0;
}

bool	init_queue(t_queue *queue, size_t capacity, t_scheduler_mode mode)
{
	if (queue == NULL || capacity == 0)
		return (false);
	queue->heap = (t_request *)malloc(sizeof(t_request) * capacity);
	if (queue->heap == NULL)
		return (false);
	queue->size = 0;
	queue->capacity = capacity;
	queue->next_sequence = 0;
	queue->mode = mode;
	return (true);
}
