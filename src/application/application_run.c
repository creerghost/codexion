/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   application_run.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/16 19:28:18 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/application_api.h"
#include "modules/coder_api.h"
#include "modules/scheduler_api.h"
#include "modules/time_api.h"
#include "modules/monitor_api.h"
#include "structs/application.h"

static void	set_start_time(t_application *app)
{
	long long	start_time;
	size_t		index;

	start_time = current_time_ms();
	app->context.start_time = start_time;
	index = 0;
	while (index < app->coders_initialized)
	{
		coder_mark_compile_start(&app->coders[index], start_time);
		index++;
	}
}

static bool	create_threads(t_application *app)
{
	size_t	index;

	if (pthread_create(&app->scheduler.thread, NULL,
			scheduler_routine, &app->scheduler) != 0)
		return (false);
	app->scheduler_thread_created = true;
	index = 0;
	while (index < app->coders_initialized)
	{
		if (pthread_create(&app->coders[index].thread, NULL,
				coder_routine, &app->coders[index]) != 0)
			return (false);
		app->coder_threads_created++;
		index++;
	}
	if (pthread_create(&app->monitor.thread, NULL,
			monitor_routine, &app->monitor) != 0)
		return (false);
	app->monitor_thread_created = true;
	return (true);
}

static bool	start_threads(t_application *app)
{
	bool	created;

	pthread_mutex_lock(&app->context.state_mutex);
	created = create_threads(app);
	if (created)
		set_start_time(app);
	else
		app->context.is_running = false;
	pthread_mutex_unlock(&app->context.state_mutex);
	return (created);
}

static void	join_created_threads(t_application *app)
{
	size_t	index;

	if (app->monitor_thread_created)
		pthread_join(app->monitor.thread, NULL);
	if (app->scheduler_thread_created)
		pthread_join(app->scheduler.thread, NULL);
	index = 0;
	while (index < app->coder_threads_created)
	{
		pthread_join(app->coders[index].thread, NULL);
		index++;
	}
}

bool	run_application(t_application *app)
{
	if (app == NULL)
		return (false);
	if (!start_threads(app))
	{
		if (app->scheduler_thread_created)
			scheduler_notify(&app->scheduler);
		join_created_threads(app);
		return (false);
	}
	join_created_threads(app);
	return (true);
}
