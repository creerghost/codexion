/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 18:15:40 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/context_api.h"
#include <stdlib.h>

bool	init_context(t_context *context, const t_args *args)
{
	if (context == NULL || args == NULL)
		return (false);
	if (pthread_mutex_init(&context->state_mutex, NULL))
		return (false);
	if (pthread_mutex_init(&context->log_mutex, NULL))
		return (pthread_mutex_destroy(&context->state_mutex), false);
	context->args = args;
	context->start_time = 0;
	context->is_running = true;
	return (true);
}

void	free_context(t_context *context)
{
	if (context == NULL)
		return ;
	context->args = NULL;
	context->start_time = 0;
	context->is_running = false;
	pthread_mutex_destroy(&context->state_mutex);
	pthread_mutex_destroy(&context->log_mutex);
}

void	stop_context(t_context *context)
{
	pthread_mutex_lock(&context->state_mutex);
	context->is_running = false;
	pthread_mutex_unlock(&context->state_mutex);
}
