/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_request.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 22:33:21 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/dongle_api.h"
#include "modules/queue_api.h"

bool	dongle_add_request(t_dongle *dongle, t_request request)
{
	if (!dongle)
		return (false);
	pthread_mutex_lock(&dongle->mutex);
	if (!queue_push(&dongle->queue, request))
		return (pthread_mutex_unlock(&dongle->mutex), false);
	pthread_mutex_unlock(&dongle->mutex);
	return (true);
}
