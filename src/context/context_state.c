/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 17:52:24 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/context_api.h"

bool	context_is_running(t_context *context)
{
	bool	running;

	if (context == NULL)
		return (false);
	pthread_mutex_lock(&context->state_mutex);
	running = (context->is_running != 0);
	pthread_mutex_unlock(&context->state_mutex);
	return (running);	
}
