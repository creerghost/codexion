/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   application_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 18:05:01 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/application_api.h"
#include "modules/coder_api.h"
#include "modules/context_api.h"
#include "modules/dongle_api.h"
#include "modules/scheduler_api.h"

void	free_application(t_application *app)
{
	if (app == NULL)
		return ;
	if (app->scheduler_initialized)
		free_scheduler(&app->scheduler);
	app->scheduler_initialized = false;
	app->monitor.context = NULL;
	app->monitor.coders = NULL;
	app->monitor.scheduler = NULL;
	app->monitor.count = 0;
	if (app->coders_initialized > 0)
		free_coders(app->coders, app->coders_initialized);
	app->coders = NULL;
	app->coders_initialized = 0;
	if (app->dongles_initialized > 0)
		free_dongles(app->dongles, app->dongles_initialized);
	app->dongles = NULL;
	app->dongles_initialized = 0;
	if (app->context_initialized)
		free_context(&app->context);
	app->context_initialized = false;
}
