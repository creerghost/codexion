/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:54:20 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/08 14:02:20 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/**
 * @brief Calculates the Earliest Deadline First (EDF) key.
 * 
 * @param coder Pointer to the coder struct.
 * @return The absolute timestamp (ms) when the coder will burn out.
 */

long	edf_key(t_coder *coder)
{
	long	release_at;

	release_at = coder->last_compile_start + coder->ctx->args->time_to_burnout;
	return (release_at);
}

/**
 * @brief Attempts to safely acquire a dongle.
 * 
 * Uses either FIFO or EDF scheduling algorithms via a priority queue.
 * 
 * @param coder Pointer to the requesting coder.
 * @param dongle Pointer to the target dongle.
 * @return true if acquired successfully, false if the sim stopped.
 */

bool	grab_dongle(t_coder *coder, t_dongle *dongle)
{
	int	tmp;

	if (!dongle)
		return (false);
	pthread_mutex_lock(&dongle->mutex);
	if (coder->ctx->args->scheduler == FIFO)
	{
		if (!ft_heappush(&dongle->heapq, coder->id, get_time_ms()))
			return (pthread_mutex_unlock(&dongle->mutex), false);
	}
	else if (coder->ctx->args->scheduler == EDF)
	{
		if (!ft_heappush(&dongle->heapq, coder->id, edf_key(coder)))
			return (pthread_mutex_unlock(&dongle->mutex), false);
	}
	while (dongle->held == true || ft_heappeek(&dongle->heapq) != coder->id)
	{
		if (!is_sim_running(coder->ctx))
			return (pthread_mutex_unlock(&dongle->mutex), false);
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
	}
	ft_heappop(&dongle->heapq, &tmp);
	dongle->held = true;
	pthread_mutex_unlock(&dongle->mutex);
	return (true);
}

/**
 * @brief Releases a dongle and signals waiting threads.
 * 
 * @param dongle Pointer to the dongle to be released.
 */

void	release_dongle(t_dongle *dongle)
{
	if (!dongle)
		return ;
	pthread_mutex_lock(&dongle->mutex);
	dongle->held = false;
	dongle->release_time = get_time_ms();
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}
