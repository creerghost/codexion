/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 18:07:36 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/12 18:34:25 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/dongle.h"
#include "structs/application.h"
#include <pthread.h>
#include <stdlib.h>

//void	init_queue();
static void	free_dongles(int idx, t_dongle *dongles);

static int	init_dongle(int idx, t_dongle *dongle)
{
	dongle->last_release_time = 0;
	if (pthread_mutex_init(&dongle->mutex, NULL))
	return (0);
//	if (!init_queue())
		//free dongles;
	return (1);
}

int	init_dongles(int num_dongles, t_application *app)
{
	int	idx;

	app->dongles = (t_dongle *)malloc(sizeof(t_dongle) * num_dongles);
	if (!app->dongles)
		return (0);	
	idx = 0;
	while (idx < num_dongles)
	{
		if (!init_dongle(&app->dongles[idx]))
			return (free_dongles(idx, app->dongles), 0);
		idx++;
	}
	return (1);
}