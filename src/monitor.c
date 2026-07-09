/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 17:41:10 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/09 18:03:04 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/**
 * Triggers the global burnout state for the simulation.
 * 
 * Logs the death and signals all threads to terminate.
 * 
 * - ctx: Pointer to the simulation context.
 * - coder_id: ID of the coder that burned out.
 * Returns: true (always).
 */

static bool	handle_burnout(t_context *ctx, int coder_id)
{
	pthread_mutex_lock(&ctx->sim_mutex);
	ctx->is_running = false;
	pthread_mutex_unlock(&ctx->sim_mutex);
	pthread_mutex_lock(&ctx->log_mutex);
	printf("%ld %d burned out\n", get_time_ms() - ctx->start_time, coder_id);
	pthread_mutex_unlock(&ctx->log_mutex);
	pthread_cond_broadcast(&ctx->done_cond);
	return (true);
}

/**
 * Triggers the global finish state when targets are met.
 * 
 * - ctx: Pointer to the simulation context.
 * Returns: true (always).
 */

static bool	handle_finish(t_context *ctx)
{
	pthread_mutex_lock(&ctx->sim_mutex);
	ctx->is_running = false;
	pthread_mutex_unlock(&ctx->sim_mutex);
	pthread_cond_broadcast(&ctx->done_cond);
	return (true);
}

/**
 * Main polling function for the monitor thread.
 * 
 * Iterates over all coders checking for burnout or completion.
 * 
 * - ctx: Pointer to the simulation context.
 * Returns: true if simulation should stop, false to continue.
 */

static bool	check_coders(t_context *ctx)
{
	int	i;
	int	finished;

	i = -1;
	finished = 0;
	while (++i < ctx->args->num_coders)
	{
		pthread_mutex_lock(&ctx->coders[i].mutex);
		if (get_time_ms()
			- ctx->coders[i].last_compile_start >= ctx->args->time_to_burnout)
			return (pthread_mutex_unlock(&ctx->coders[i].mutex),
				handle_burnout(ctx, ctx->coders[i].id), true);
		if (ctx->args->num_compiles_req > 0
			&& ctx->coders[i].compile_count >= ctx->args->num_compiles_req)
			finished++;
		pthread_mutex_unlock(&ctx->coders[i].mutex);
	}
	if (ctx->args->num_compiles_req > 0 && finished == ctx->args->num_coders)
		return (handle_finish(ctx), true);
	return (false);
}

/**
 * Main execution routine for the monitor thread.
 * 
 * Periodically checks all coders for burnout or completion. Signals the
 * simulation to stop if a burnout occurs or all targets are met.
 * 
 * - arg: Pointer to the simulation context.
 * Returns: NULL.
 */
void	*monitor_routine(void *arg)
{
	t_context	*ctx;

	ctx = (t_context *)arg;
	while (is_sim_running(ctx))
	{
		if (check_coders(ctx))
			break ;
		usleep(1000);
	}
	return (NULL);
}
