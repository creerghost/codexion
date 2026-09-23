/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 23:17:48 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/logger_api.h"
#include "modules/time_api.h"
#include "modules/context_api.h"
#include <stdio.h>

void	log_state(t_context *context, int coder_id, const char *state)
{
	pthread_mutex_lock(&context->log_mutex);
	if (context_is_running(context))
		printf("%lld %i %s\n",
			simulation_time_ms(context), coder_id, state);
	pthread_mutex_unlock(&context->log_mutex);
}

void	log_compile_start(t_context *context, int coder_id)
{
	long long	timestamp;

	pthread_mutex_lock(&context->log_mutex);
	if (context_is_running(context))
	{
		timestamp = simulation_time_ms(context);
		printf("%lld %i has taken a dongle\n", timestamp, coder_id);
		printf("%lld %i has taken a dongle\n", timestamp, coder_id);
		printf("%lld %i is compiling\n", timestamp, coder_id);
	}
	pthread_mutex_unlock(&context->log_mutex);
}

void	log_burnout(t_context *context, int coder_id)
{
	pthread_mutex_lock(&context->log_mutex);
	printf("%lld %d burned out\n",
		simulation_time_ms(context), coder_id);
	pthread_mutex_unlock(&context->log_mutex);
}
