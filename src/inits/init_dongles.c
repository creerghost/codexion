/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 23:54:54 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/09 01:16:36 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void free_dongles(t_context *ctx, unsigned int amount)
{
    unsigned int    i;

    i = 0;
    if (!ctx->dongles)
        return ;
    while (i < amount)
    {
        ft_heapfree(&ctx->dongles[i].heapq);
        pthread_mutex_destroy(&ctx->dongles[i].mutex);
        pthread_cond_destroy(&ctx->dongles[i].cond);
        i++;
    }
    free(ctx->dongles);
    ctx->dongles = NULL;
}

static bool init_single_dongle(t_context *ctx, int i)
{
    ctx->dongles[i].held = false;
    ctx->dongles[i].release_time = 0;
    if (!ft_heap_new(&ctx->dongles[i].heapq, ctx->args->num_coders))
        return (false);
    if (pthread_mutex_init(&ctx->dongles[i].mutex, NULL) != 0)
        return (ft_heapfree(&ctx->dongles[i].heapq), false);
    if (pthread_cond_init(&ctx->dongles[i].cond, NULL) != 0)
        return (pthread_mutex_destroy(&ctx->dongles[i].mutex),
                ft_heapfree(&ctx->dongles[i].heapq), false);
    return (true);
}

bool init_dongles(t_context *ctx)
{
    int i;

    ctx->dongles = (t_dongle *)ft_calloc(ctx->args->num_coders * sizeof(t_dongle));
    if (!ctx->dongles)
        return (false);
    i = 0;
    while (i < ctx->args->num_coders)
        if (!init_single_dongle(ctx, i++))
            return (free_dongles(ctx, i), false);
    return (true);
}