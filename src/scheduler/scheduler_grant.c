/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_grant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 22:50:05 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/scheduler_api.h"

void	scheduler_notify(t_scheduler *scheduler)
{
	if (!scheduler)
		return ;
	pthread_mutex_lock(&scheduler->mutex);
	scheduler->notified = true;
	pthread_cond_signal(&scheduler->condition);
	pthread_mutex_unlock(&scheduler->mutex);
}
