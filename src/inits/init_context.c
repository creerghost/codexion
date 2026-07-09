/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_context.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:54:20 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/08 14:02:20 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	free_context(t_context *ctx)
{
	if (ctx->dongles)
		free_dongles(ctx, ctx->args->num_coders);
	if (ctx->coders)
		free_coders(ctx, ctx->args->num_coders);
	if (ctx->args)
		free(ctx->args);
	pthread_mutex_destroy(&ctx->log_mutex);
	pthread_mutex_destroy(&ctx->sim_mutex);
	pthread_cond_destroy(&ctx->done_cond);
}

static void	init_context_zero(t_context *ctx)
{
	ctx->args = NULL;
	ctx->coders = NULL;
	ctx->dongles = NULL;
	ctx->active_coders = 0;
	ctx->start_time = 0;
	ctx->is_running = true;
}

bool	init_context(int argc, char **argv, t_context *ctx)
{
	init_context_zero(ctx);
	ctx->args = (t_args *)malloc(sizeof(t_args));
	if (!ctx->args)
		return (false);
	if (!parse_args(argc, argv, ctx))
		return (free_context(ctx), false);
	if (pthread_mutex_init(&ctx->log_mutex, NULL) != 0)
		return (free_context(ctx), false);
	if (pthread_mutex_init(&ctx->sim_mutex, NULL) != 0)
		return (free_context(ctx), false);
	if (pthread_cond_init(&ctx->done_cond, NULL) != 0)
		return (free_context(ctx), false);
	if (!init_coders(ctx))
		return (free_context(ctx), false);
	if (!init_dongles(ctx))
		return (free_context(ctx), false);
	return (true);
}
