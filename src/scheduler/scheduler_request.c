/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_request.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:45:42 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/14 13:53:44 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/scheduler_api.h"
#include "modules/coder_api.h"
#include "modules/context_api.h"
#include "modules/dongle_api.h"
#include "structs/args.h"

static bool	create_request(t_request *request, t_coder *coder)
{
	long long	last_compile;

	last_compile = coder_last_compile(coder);
	if (last_compile < 0)
		return (false);
	request->coder_id = coder->id;
	request->deadline = last_compile + coder->context->args->time_to_burnout;
	request->sequence = 0;
	return (true);
}

static bool	add_requests(t_request *request, t_coder *coder)
{
	if (coder->left_dongle == coder->right_dongle)
		return (dongle_add_request(coder->left_dongle, *request));
	if (!dongle_add_request(coder->left_dongle, *request))
		return (false);
	if (!dongle_add_request(coder->right_dongle, *request))
		return (false);
	return (true);
}

bool	scheduler_request(t_scheduler *scheduler, t_coder *coder)
{
	t_request	request;

	if (scheduler == NULL || coder == NULL || coder->context == NULL
		|| coder->context->args == NULL || coder->left_dongle == NULL
		|| coder->right_dongle == NULL || coder->scheduler != scheduler)
		return (false);
	pthread_mutex_lock(&scheduler->mutex);
	if (!context_is_running(coder->context))
		return (pthread_mutex_unlock(&scheduler->mutex), false);
	if (!create_request(&request, coder) || !add_requests(&request, coder))
		return (pthread_mutex_unlock(&scheduler->mutex), false);
	scheduler->notified = true;
	pthread_cond_signal(&scheduler->condition);
	pthread_mutex_unlock(&scheduler->mutex);
	return (true);
}
