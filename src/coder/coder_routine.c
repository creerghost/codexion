/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/16 12:58:11 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/coder_api.h"
#include "modules/scheduler_api.h"
#include "modules/context_api.h"
#include "modules/dongle_api.h"
#include "modules/gate_api.h"
#include "modules/logger_api.h"
#include "modules/time_api.h"
#include "structs/args.h"

static void	release_coder_dongles(t_coder *coder)
{
	long long	release_time;
	long long	cooldown;

	release_time = current_time_ms();
	cooldown = coder->context->args->dongle_cooldown;
	dongle_release(coder->left_dongle, release_time, cooldown);
	if (coder->right_dongle != coder->left_dongle)
		dongle_release(coder->right_dongle, release_time, cooldown);
	scheduler_notify(coder->scheduler);
}

static bool	compile_code(t_coder *coder)
{
	long long	start_time;

	log_state(coder->context, coder->id, "has taken a dongle");
	log_state(coder->context, coder->id, "has taken a dongle");
	start_time = current_time_ms();
	pthread_mutex_lock(&coder->data_mutex);
	coder->last_compile_start = start_time;
	pthread_mutex_unlock(&coder->data_mutex);
	log_state(coder->context, coder->id, "is compiling");
	interruptible_sleep(coder->context,
		coder->context->args->time_to_compile);
	release_coder_dongles(coder);
	if (!context_is_running(coder->context))
		return (false);
	pthread_mutex_lock(&coder->data_mutex);
	coder->compiles_done++;
	pthread_mutex_unlock(&coder->data_mutex);
	return (true);
}

static bool	run_coder_cycle(t_coder *coder)
{
	if (!scheduler_request(coder->scheduler, coder))
	{
		stop_context(coder->context);
		scheduler_notify(coder->scheduler);
		return (false);
	}
	gate_wait(&coder->gate);
	if (!context_is_running(coder->context) || !compile_code(coder))
		return (false);
	log_state(coder->context, coder->id, "is debugging");
	interruptible_sleep(coder->context, coder->context->args->time_to_debug);
	if (!context_is_running(coder->context))
		return (false);
	log_state(coder->context, coder->id, "is refactoring");
	interruptible_sleep(coder->context,
		coder->context->args->time_to_refactor);
	return (context_is_running(coder->context));
}

void	*coder_routine(void *argument)
{
	t_coder	*coder;

	coder = (t_coder *)argument;
	while (context_is_running(coder->context))
	{
		if (!run_coder_cycle(coder))
			break ;
	}
	return (NULL);
}
