/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:54:20 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/08 14:02:20 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static char	*get_arg_name(int idx)
{
	if (idx == 1)
		return ("number_of_coders");
	if (idx == 2)
		return ("time_to_burnout");
	if (idx == 3)
		return ("time_to_compile");
	if (idx == 4)
		return ("time_to_debug");
	if (idx == 5)
		return ("time_to_refactor");
	if (idx == 6)
		return ("number_of_compiles_required");
	return ("dongle_cooldown");
}

static int	validate_positive(int *parsed)
{
	if (parsed[0] == 0)
		return (fprintf(stderr, must_be(), get_arg_name(1), "positive"), 0);
	if (parsed[5] == 0)
		return (fprintf(stderr, must_be(), get_arg_name(6), "positive"), 0);
	return (1);
}

static int	assign_args(t_context *ctx, int *parsed, char *sched)
{

	ctx->args->num_coders = parsed[0];
	ctx->args->time_to_burnout = parsed[1];
	ctx->args->time_to_compile = parsed[2];
	ctx->args->time_to_debug = parsed[3];
	ctx->args->time_to_refactor = parsed[4];
	ctx->args->num_compiles_req = parsed[5];
	ctx->args->dongle_cooldown = parsed[6];
	if (!strcmp(sched, "FIFO") || !strcmp(sched, "fifo"))
		ctx->args->scheduler = FIFO;
	else if (!strcmp(sched, "EDF") || !strcmp(sched, "edf"))
		ctx->args->scheduler = EDF;
	else
		return (fprintf(stderr, must_be(), "scheduler",
						"fifo or edf"), 0);
	return (1);
}

int	parse_args(int ac, char **av, t_context *ctx)
{
	int	i;
	int	parsed[7];

	if (ac != 9)
		return (printf("%s", not_enough_arg()), 0);
	i = 1;
	while (i < 8)
	{
		if (!uatol(av[i], &parsed[i - 1]))
			return (fprintf(stderr, must_be(), get_arg_name(i),
					"non-negative integer"), 0);
		i++;
	}
	if (!validate_positive(parsed))
		return (0);
	return (assign_args(ctx, parsed, av[8]));
}
