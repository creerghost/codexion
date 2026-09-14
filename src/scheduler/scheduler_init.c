/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 22:00:40 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/scheduler_api.h"
#include "structs/args.h"
#include "structs/coder.h"
#include "structs/context.h"

static void	set_coder_scheduler_links(t_coder *coders, size_t count,
		t_scheduler *value)
{
	size_t	index;

	index = 0;
	while (index < count)
	{
		coders[index].scheduler = value;
		index++;
	}
}

void	free_scheduler(t_scheduler *scheduler)
{
	if (scheduler == NULL || scheduler->context == NULL)
		return ;
	set_coder_scheduler_links(scheduler->coders, scheduler->count, NULL);
	pthread_cond_destroy(&scheduler->condition);
	pthread_mutex_destroy(&scheduler->mutex);
	scheduler->context = NULL;
	scheduler->coders = NULL;
	scheduler->dongles = NULL;
	scheduler->count = 0;
	scheduler->notified = false;
}

bool	init_scheduler(t_scheduler *scheduler, t_context *context,
			t_coder *coders, t_dongle *dongles)
{
	if (scheduler == NULL || context == NULL || context->args == NULL
		|| coders == NULL || dongles == NULL)
		return (false);
	scheduler->context = NULL;
	scheduler->count = 0;
	scheduler->notified = false;
	if (pthread_mutex_init(&scheduler->mutex, NULL))
		return (false);
	if (pthread_cond_init(&scheduler->condition, NULL))
		return (pthread_mutex_destroy(&scheduler->mutex), false);
	scheduler->context = context;
	scheduler->coders = coders;
	scheduler->dongles = dongles;
	scheduler->count = (size_t)context->args->num_coders;
	set_coder_scheduler_links(coders, scheduler->count, scheduler);
	return (true);
}
