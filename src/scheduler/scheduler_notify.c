/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_notify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 00:00:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/17 00:00:00 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/scheduler_api.h"

void	scheduler_notify(t_scheduler *scheduler)
{
	if (!scheduler)
		return ;
	pthread_mutex_lock(&scheduler->mutex);
	scheduler->notified = true;
	pthread_cond_broadcast(&scheduler->condition);
	pthread_mutex_unlock(&scheduler->mutex);
}
