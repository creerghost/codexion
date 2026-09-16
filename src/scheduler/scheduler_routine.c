/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/16 12:56:25 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/context_api.h"
#include "modules/gate_api.h"
#include "modules/scheduler_api.h"
#include "scheduler_internal.h"
#include "modules/time_api.h"
#include "structs/coder.h"
#include "structs/dongle.h"

static bool	next_cooldown_deadline(t_scheduler *scheduler,
		long long now, long long *deadline)
{
	size_t		index;
	t_dongle	*dongle;
	bool		found;

	index = 0;
	found = false;
	while (index < scheduler->count)
	{
		dongle = &scheduler->dongles[index];
		pthread_mutex_lock(&dongle->mutex);
		if (dongle->queue.size > 0 && !dongle->is_busy
			&& dongle->available_at > now
			&& (!found || dongle->available_at < *deadline))
		{
			*deadline = dongle->available_at;
			found = true;
		}
		pthread_mutex_unlock(&dongle->mutex);
		index++;
	}
	return (found);
}

static void	scheduler_wait_locked(t_scheduler *scheduler)
{
	struct timespec	timeout;
	long long		deadline;
	long long		now;

	scheduler->notified = false;
	now = current_time_ms();
	if (next_cooldown_deadline(scheduler, now, &deadline))
	{
		timeout.tv_sec = deadline / 1000;
		timeout.tv_nsec = (deadline % 1000) * 1000000;
		pthread_cond_timedwait(&scheduler->condition,
			&scheduler->mutex, &timeout);
	}
	else
	{
		while (!scheduler->notified
			&& context_is_running(scheduler->context))
			pthread_cond_wait(&scheduler->condition, &scheduler->mutex);
	}
}

static void	wake_coder_gates(t_scheduler *scheduler)
{
	size_t	index;

	index = 0;
	while (index < scheduler->count)
	{
		gate_open(&scheduler->coders[index].gate);
		index++;
	}
}

void	*scheduler_routine(void *argument)
{
	t_scheduler	*scheduler;
	long long	time_now;

	scheduler = (t_scheduler *)argument;
	pthread_mutex_lock(&scheduler->mutex);
	while (context_is_running(scheduler->context))
	{
		time_now = current_time_ms();
		if (!scheduler_try_grant_locked(scheduler, time_now))
			scheduler_wait_locked(scheduler);
	}
	wake_coder_gates(scheduler);
	pthread_mutex_unlock(&scheduler->mutex);
	return (NULL);
}
