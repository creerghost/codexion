/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_api.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 21:21:46 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_API_H
# define QUEUE_API_H

# include <stdbool.h>
# include "structs/queue.h"

bool	init_queue(t_queue *queue, size_t capacity, t_scheduler_mode mode);
void	free_queue(t_queue *queue);
bool	queue_push(t_queue *queue, t_request request);
bool	queue_pop(t_queue *queue, t_request *request);
bool	queue_peek(const t_queue *queue, t_request *request);

#endif
