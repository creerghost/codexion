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

static bool	handle_finish(t_context *ctx)
{
	pthread_mutex_lock(&ctx->sim_mutex);
	ctx->is_running = false;
	pthread_mutex_unlock(&ctx->sim_mutex);
	pthread_cond_broadcast(&ctx->done_cond);
	return (true);
}

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
