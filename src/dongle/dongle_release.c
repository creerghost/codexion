/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_release.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 22:34:51 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/dongle_api.h"

void	dongle_release(t_dongle *dongle, long long release_time,
			long long cooldown)
{
	if (!dongle)
		return ;
	pthread_mutex_lock(&dongle->mutex);
	dongle->is_busy = false;
	dongle->available_at = release_time + cooldown;
	pthread_mutex_unlock(&dongle->mutex);
}
