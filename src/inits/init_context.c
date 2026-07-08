/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_context.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:54:57 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/09 01:00:19 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void free_context(t_context *ctx)
{
    if (ctx->dongles)
        free_dongles(ctx, ctx->args->num_coders);
    if (ctx->coders)
        free_coders(ctx, ctx->args->num_coders);
    if (ctx->args)
        free(ctx->args);
}

static void	init_context_zero(t_context *ctx)
{
	ctx->args = NULL;
	ctx->coders = NULL;
	ctx->dongles = NULL;
	ctx->active_coders = 0;
	ctx->start_time = 0;
}

bool    init_context(int argc, char **argv, t_context *ctx)
{
    init_context_zero(ctx);
    ctx->args = (t_args *)malloc(sizeof(t_args));
    if (!ctx->args)
        return (false);
    if (!parse_args(argc, argv, ctx))
        return (free_context(ctx), false);
    if (!init_coders(ctx))
        return (free_context(ctx), false);
    if (!init_dongles(ctx))
        return (free_context(ctx), false);
    
    return (true);
}