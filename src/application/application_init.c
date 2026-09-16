/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   application_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/16 18:41:11 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "modules/application_api.h"
#include "modules/dongle_api.h"
#include "modules/parser_api.h"
#include "modules/context_api.h"
#include "modules/coder_api.h"
#include "modules/scheduler_api.h"
#include "modules/monitor_api.h"

static bool	init_resources(t_application *app)
{
	size_t	count;

	count = (size_t)app->args.num_coders;
	if (!init_dongles(&app->dongles, count, app->args.scheduler))
		return (false);
	app->dongles_initialized = count;
	if (!init_coders(&app->coders, count,
			&app->context, app->dongles))
		return (false);
	app->coders_initialized = count;
	if (!init_scheduler(&app->scheduler, &app->context,
			app->coders, app->dongles))
		return (false);
	app->scheduler_initialized = true;
	init_monitor(&app->monitor, &app->scheduler);
	return (true);
}

bool	init_application(t_application *app, int ac, char **av)
{
	if (app == NULL)
		return (false);
	memset(app, 0, sizeof(*app));
	if (!parse_args(ac, av, &app->args))
		return (false);
	if (!init_context(&app->context, &app->args))
		return (false);
	app->context_initialized = true;
	if (!init_resources(app))
		return (free_application(app), false);
	return (true);
}
