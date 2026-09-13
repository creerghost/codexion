/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 21:48:18 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/dongle_api.h"
#include "modules/queue_api.h"
#include <stdlib.h>

void	free_dongles(t_dongle *dongles, size_t count)
{
	size_t	index;

	if (dongles == NULL)
		return ;
	index = 0;
	while (index < count)
	{
		free_queue(&dongles[index].queue);
		pthread_mutex_destroy(&dongles[index].mutex);
		index++;
	}
	free(dongles);
}

static bool	init_dongle(t_dongle *dongle, t_scheduler_mode mode,
		size_t capacity)
{
	dongle->is_busy = false;
	dongle->available_at = 0;
	if (pthread_mutex_init(&dongle->mutex, NULL))
		return (false);
	if (!init_queue(&dongle->queue, capacity, mode))
		return (pthread_mutex_destroy(&dongle->mutex), false);
	return (true);
}

bool	init_dongles(t_dongle **dongles, size_t count,
		t_scheduler_mode mode)
{
	size_t		index;
	t_dongle	*new_dongles;

	if (dongles == NULL || count == 0)
		return (false);
	new_dongles = (t_dongle *)malloc(sizeof(t_dongle) * count);
	if (!new_dongles)
		return (false);
	index = 0;
	while (index < count)
	{
		new_dongles[index].id = (int)index;
		if (!init_dongle(&new_dongles[index], mode, count))
			return (free_dongles(new_dongles, index), false);
		index++;
	}
	*dongles = new_dongles;
	return (true);
}
