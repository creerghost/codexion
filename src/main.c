/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:54:20 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/08 14:02:20 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/**
 * Joins all active coder and monitor threads, waiting for them to finish.
 * 
 * - ctx: Pointer to the simulation context.
 * Returns: true if all threads were joined successfully.
 */
static void	stop_sim(t_context *ctx, int num_to_join)
{
	int	i;

	pthread_mutex_lock(&ctx->sim_mutex);
	ctx->is_running = false;
	pthread_mutex_unlock(&ctx->sim_mutex);
	pthread_cond_broadcast(&ctx->done_cond);
	i = 0;
	while (i < num_to_join)
	{
		pthread_join(ctx->coders[i].thread_id, NULL);
		i++;
	}
}

/**
 * Spawns all coder and monitor threads to begin the simulation.
 * 
 * - ctx: Pointer to the simulation context.
 * Returns: true if all threads spawned successfully, false otherwise.
 */
static bool	start_sim(t_context *ctx)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	ctx->start_time = get_time_ms();
	while (i < ctx->args->num_coders)
	{
		ctx->coders[i].last_compile_start = ctx->start_time;
		if (pthread_create(&ctx->coders[i].thread_id, NULL,
				coder_routine, &ctx->coders[i]) != 0)
			return (stop_sim(ctx, i), false);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, ctx) != 0)
		return (stop_sim(ctx, ctx->args->num_coders), false);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < ctx->args->num_coders)
		pthread_join(ctx->coders[i++].thread_id, NULL);
	return (true);
}

/**
 * Entry point for the Codexion simulation program.
 * 
 * Parses arguments, initializes the context, starts the simulation,
 * waits for completion, and cleans up resources.
 * 
 * - argc: Argument count.
 * - argv: Argument vector.
 * Returns: 0 on success, 1 on error.
 */
int	main(int argc, char **argv)
{
	t_context	ctx;

	if (!init_context(argc, argv, &ctx))
		return (1);
	if (!start_sim(&ctx))
	{
		free_context(&ctx);
		return (1);
	}
	free_context(&ctx);
	return (0);
}
