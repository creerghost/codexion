/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:54:20 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/08 14:02:20 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <sys/time.h>
#include <unistd.h>

/**
 * Wrapper of gettimeofday.
 *
 * Returns: The current time in milliseconds.
 */
long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/**
 * Precise sleep using usleep() + busy-wait tail.
 *
 * - duration_ms: Duration to sleep in milliseconds.
 * - ctx: Pointer to the simulation context.
 */
void	ft_sleep(long duration_ms, t_context *ctx)
{
	long	target;
	long	remaining;

	target = get_time_ms() + duration_ms;
	while (get_time_ms() < target)
	{
		if (!is_sim_running(ctx))
			return ;
		remaining = target - get_time_ms();
		if (remaining > 1)
			usleep(500);
		else
			usleep(100);
	}
}

/**
 * Returns the time elapsed since the simulation started.
 *
 * - ctx: Pointer to the simulation context.
 * Returns: The elapsed time in milliseconds.
 */
long	elapsed_ms(t_context *ctx)
{
	return (get_time_ms() - ctx->start_time);
}
