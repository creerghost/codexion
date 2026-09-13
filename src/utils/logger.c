/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 22:49:10 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/logger_api.h"
#include <stdio.h>

void	log_state(t_context *context, int coder_id, const char *state)
{
	pthread_mutex_lock(&context->state_mutex);
	printf("%d %lld %s\n", coder_id, context->start_time, state);
	pthread_mutex_unlock(&context->state_mutex);
}

void	log_burnout(t_context *context, int coder_id)
{
	pthread_mutex_lock(&context->log_mutex);
	printf("%i burned out\n", coder_id);
	pthread_mutex_lock(&context->log_mutex);
}
