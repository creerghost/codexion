/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   application_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 18:03:33 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "modules/application_api.h"
#include "modules/parser_api.h"
#include "modules/context_api.h"

bool	init_application(t_application *app, int ac, char **av)
{
	if (app == NULL)
		return (false);
	memset(app, 0, sizeof(*app));
	if (!parse_args(ac, av, &app->args))
		return (false);
	if (!init_context(&app->context, &app->args))
		return (false);
	app->context_initialized = 1;
	return (true);	
}
