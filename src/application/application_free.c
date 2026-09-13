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
#include "modules/context_api.h"

void	free_application(t_application *app)
{
	if (app == NULL)
		return ;
	if (app->context_initialized)
	{
		free_context(&app->context);
		app->context_initialized = 0;
	}
}
