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

void	free_dongles(t_dongle *dongles, int count)
{
	int	idx;

	if (dongles == NULL)
		return ;
	idx = 0;
	while (idx < count)
	{
		free_queue(&dongles[idx].queue);
		pthread_mutex_destroy(&dongles[idx].mutex);
		idx++;
	}
	free(dongles);
}

static bool	init_dongle(t_dongle *dongle, t_scheduler_mode mode, int capacity)
{
	dongle->is_busy = 0;
	dongle->available_at = 0;
	if (pthread_mutex_init(&dongle->mutex, NULL))
		return (false);
	if (!init_queue(&dongle->queue, capacity, mode))
		return (pthread_mutex_destroy(&dongle->mutex), false);
	return (true);
}

bool	init_dongles(t_dongle **dongles, int count, t_scheduler_mode mode)
{
	int			idx;
	t_dongle	*new_dongles;

	if (dongles == NULL || count <= 0)
		return (false);
	new_dongles = (t_dongle *)malloc(sizeof(t_dongle) * count);
	if (!new_dongles)
		return (false);
	idx = 0;
	while (idx < count)
	{
		new_dongles[idx].id = idx;
		if (!init_dongle(&new_dongles[idx], mode, count))
			return (free_dongles(new_dongles, idx), false);
		idx++;
	}
	*dongles = new_dongles;
	return (true);
}
