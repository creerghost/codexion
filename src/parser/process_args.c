/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 00:42:59 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/09 01:17:39 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "atoi.h"
#include "parse.h"

static int	validate_if_positive(int i, int num)
{
	if (i == 1 || i == 6)
		return (num > 0);
	return (num >= 0);
}

static int	assign_args(t_args *args, int *nums, char *sched)
{
	args->num_coders = nums[0];
	args->time_to_burnout = nums[1];
	args->time_to_compile = nums[2];
	args->time_to_debug = nums[3];
	args->time_to_refactor = nums[4];
	args->num_compiles_req = nums[5];
	args->dongle_cooldown = nums[6];
	if (strcmp(sched, "fifo") == 0)
		args->scheduler = FIFO;
	else if (strcmp(sched, "edf") == 0)
		args->scheduler = EDF;
	else
		return (fprintf(stderr, "Error: scheduler must be \"fifo\" or "
				"\"edf\"\n"), 0);
	return (1);
}

int	parse_args(int ac, char **av, t_args *args)
{
	int	i;
	int	nums[7];

	if (ac != 9)
		return (printf("Usage: ./codexion <number_of_coders> "
				"<time_to_burnout> <time_to_compile> "
				"<time_to_debug> <time_to_refactor> "
				"<number_of_compiles_required> <dongle_cooldown> "
				"<scheduler>\n"), 0);
	i = 1;
	while (i < 8)
	{
		if (!atoi_flagged(av[i], &nums[i - 1]))
			return (fprintf(stderr, "Error: argument %i must be a "
					"non-negative integer\n", i), 0);
		if (!validate_if_positive(i, nums[i - 1]))
			return (fprintf(stderr, "Error: argument %i must be "
					"positive\n", i), 0);
		i++;
	}
	return (assign_args(args, nums, av[8]));
}
