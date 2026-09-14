/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_grant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/14 15:16:33 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/scheduler_api.h"
#include "scheduler_internal.h"
#include "modules/gate_api.h"
#include "modules/queue_api.h"
#include "structs/coder.h"
#include "structs/dongle.h"

void	scheduler_notify(t_scheduler *scheduler)
{
	if (!scheduler)
		return ;
	pthread_mutex_lock(&scheduler->mutex);
	scheduler->notified = true;
	pthread_cond_signal(&scheduler->condition);
	pthread_mutex_unlock(&scheduler->mutex);
}

static bool	dongles_available_for(t_coder *coder, long long now)
{
	t_request	left_request;
	t_request	right_request;

	if (coder->left_dongle->is_busy || coder->right_dongle->is_busy)
		return (false);
	if (coder->left_dongle->available_at > now
		|| coder->right_dongle->available_at > now)
		return (false);
	if (!queue_peek(&coder->left_dongle->queue, &left_request)
		|| !queue_peek(&coder->right_dongle->queue, &right_request))
		return (false);
	return (left_request.coder_id == coder->id
		&& right_request.coder_id == coder->id);
}

static void	lock_coder_dongles(t_coder *coder, t_dongle **first,
		t_dongle **second)
{
	if (coder->left_dongle->id < coder->right_dongle->id)
	{
		*first = coder->left_dongle;
		*second = coder->right_dongle;
	}
	else
	{
		*first = coder->right_dongle;
		*second = coder->left_dongle;
	}
	pthread_mutex_lock(&(*first)->mutex);
	pthread_mutex_lock(&(*second)->mutex);
}

static bool	try_grant_coder(t_coder *coder, long long now)
{
	t_dongle	*first;
	t_dongle	*second;
	t_request	request;

	if (coder->left_dongle == coder->right_dongle)
		return (false);
	lock_coder_dongles(coder, &first, &second);
	if (!dongles_available_for(coder, now))
	{
		pthread_mutex_unlock(&second->mutex);
		pthread_mutex_unlock(&first->mutex);
		return (false);
	}
	queue_pop(&coder->left_dongle->queue, &request);
	queue_pop(&coder->right_dongle->queue, &request);
	coder->left_dongle->is_busy = true;
	coder->right_dongle->is_busy = true;
	pthread_mutex_unlock(&second->mutex);
	pthread_mutex_unlock(&first->mutex);
	gate_open(&coder->gate);
	return (true);
}

bool	scheduler_try_grant_locked(t_scheduler *scheduler, long long now)
{
	size_t	index;

	index = 0;
	while (index < scheduler->count)
	{
		if (try_grant_coder(&scheduler->coders[index], now))
			return (true);
		index++;
	}
	return (false);
}
