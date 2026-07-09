/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:54:20 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/08 14:02:20 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	free_coders(t_context *ctx, unsigned int amount)
{
	unsigned int	i;

	i = 0;
	if (!ctx->coders)
		return ;
	while (i < amount)
		pthread_mutex_destroy(&ctx->coders[i++].mutex);
	free(ctx->coders);
	ctx->coders = NULL;
}

static bool	init_single_coder(t_context *ctx, int i)
{
	ctx->coders[i].id = i + 1;
	ctx->coders[i].compile_count = 0;
	ctx->coders[i].last_compile_start = 0;
	ctx->coders[i].left_dongle = i;
	ctx->coders[i].right_dongle = (i + 1) % ctx->args->num_coders;
	ctx->coders[i].first_dongle = ft_min(ctx->coders[i].left_dongle,
			ctx->coders[i].right_dongle);
	ctx->coders[i].second_dongle = ft_max(ctx->coders[i].left_dongle,
			ctx->coders[i].right_dongle);
	ctx->coders[i].ctx = ctx;
	if (pthread_mutex_init(&ctx->coders[i].mutex, NULL) != 0)
		return (false);
	return (true);
}

bool	init_coders(t_context *ctx)
{
	int	i;

	ctx->coders = (t_coder *)ft_calloc(ctx->args->num_coders * sizeof(t_coder));
	if (!ctx->coders)
		return (false);
	i = 0;
	while (i < ctx->args->num_coders)
		if (!init_single_coder(ctx, i++))
			return (free_coders(ctx, i), false);
	return (true);
}
