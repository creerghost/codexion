/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/16 18:35:30 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/monitor_api.h"
#include "structs/scheduler.h"

void	init_monitor(t_monitor *monitor, t_scheduler *scheduler)
{
	monitor->context = scheduler->context;
	monitor->coders = scheduler->coders;
	monitor->scheduler = scheduler;
	monitor->count = scheduler->count;
}
