/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/16 18:54:12 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/coder_api.h"
#include "modules/logger_api.h"
#include "modules/monitor_api.h"
#include "modules/scheduler_api.h"
#include "modules/time_api.h"
#include "modules/context_api.h"
#include <unistd.h>

static int	find_burned_out(t_monitor *monitor, long long now)
{
	long long	last_compile;
	size_t		index;

	index = 0;
	while (index < monitor->count)
	{
		last_compile = coder_last_compile(&monitor->coders[index]);
		if (now > last_compile
			+ monitor->context->args->time_to_burnout)
			return (monitor->coders[index].id);
		index++;
	}
	return (0);
}

static bool	all_coders_finished(t_monitor *monitor)
{
	size_t	index;

	index = 0;
	while (index < monitor->count)
	{
		if (coder_compile_count(&monitor->coders[index])
			< monitor->context->args->num_compiles_req)
			return (false);
		index++;
	}
	return (true);
}

static void	stop_monitor(t_monitor *monitor, int burned_out_id)
{
	stop_context(monitor->context);
	if (burned_out_id > 0)
		log_burnout(monitor->context, burned_out_id);
	scheduler_notify(monitor->scheduler);
}

void	*monitor_routine(void *argument)
{
	t_monitor	*monitor;
	int			burned_out_id;

	monitor = (t_monitor *)argument;
	while (context_is_running(monitor->context))
	{
		burned_out_id = find_burned_out(monitor, current_time_ms());
		if (burned_out_id > 0 || all_coders_finished(monitor))
		{
			stop_monitor(monitor, burned_out_id);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
