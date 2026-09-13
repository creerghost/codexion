/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 17:41:42 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/time_api.h"
#include <sys/time.h>
#include <unistd.h>
#include "modules/context_api.h"

long long	current_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == 0)
		return (0);
	return ((time.tv_sec * 1000LL) + (time.tv_usec) / 1000);
}

long long	simulation_time_ms(t_context *context)
{
	return (current_time_ms() - context->start_time);
}

void	interruptible_sleep(t_context *context, long long duration)
{
	long long	end;

	end = current_time_ms() + duration;
	while (context_is_running(context) && current_time_ms() < end)
		usleep(500);
}
