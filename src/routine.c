/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 17:10:57 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/09 17:37:02 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/**
 * Safely grabs two required dongles without causing deadlock.
 * 
 * Enforces ascending ID order when acquiring dongles.
 * 
 * - coder: Pointer to the coder.
 * - d1: First required dongle.
 * - d2: Second required dongle.
 * Returns: true if both acquired successfully, false otherwise.
 */

static bool	grab_two_dongles(t_coder *coder, t_dongle *d1, t_dongle *d2)
{
	if (!grab_dongle(coder, d1))
		return (false);
	if (!grab_dongle(coder, d2))
		return (release_dongle(d1), false);
	return (true);
}

/**
 * Executes the compilation phase of the coder's lifecycle.
 * 
 * Grabs necessary dongles, sleeps, updates state, and drops dongles.
 * 
 * - coder: Pointer to the executing coder.
 * Returns: true if successful, false if starvation occurred.
 */

static void	compile(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
	coder->compile_count++;
	coder->last_compile_start = get_time_ms();
	pthread_mutex_unlock(&coder->mutex);
	log_msg(coder->ctx, coder->id, "is compiling");
	ft_sleep(coder->ctx->args->time_to_compile, coder->ctx);
}

/**
 * Main execution routine for each coder thread.
 * 
 * Handles the thinking, compiling, and refactoring lifecycle until burnout
 * or required compiles are met.
 * 
 * - arg: Pointer to the coder struct.
 * Returns: NULL.
 */
void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->ctx->args->num_coders == 1)
	{
		grab_dongle(coder, coder->ctx->dongles + coder->first_dongle);
		while (is_sim_running(coder->ctx))
			ft_sleep(10, coder->ctx);
		release_dongle(coder->ctx->dongles + coder->first_dongle);
		return (NULL);
	}
	while (is_sim_running(coder->ctx))
	{
		if (!grab_two_dongles(coder, coder->ctx->dongles + coder->first_dongle,
				coder->ctx->dongles + coder->second_dongle))
			break ;
		compile(coder);
		release_dongle(coder->ctx->dongles + coder->first_dongle);
		release_dongle(coder->ctx->dongles + coder->second_dongle);
		log_msg(coder->ctx, coder->id, "is debugging");
		ft_sleep(coder->ctx->args->time_to_debug, coder->ctx);
		log_msg(coder->ctx, coder->id, "is refactoring");
		ft_sleep(coder->ctx->args->time_to_refactor, coder->ctx);
	}
	return (NULL);
}
