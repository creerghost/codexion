/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 14:13:54 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "modules/parser_api.h"

static int	validate_if_positive(int i, int num)
{
	if (i == 1 || i == 6)
		return (num > 0);
	return (num >= 0);
}

static int	assign_args(t_args *args, int *nums, char *scheduler)
{
	args->num_coders = nums[0];
	args->time_to_burnout = nums[1];
	args->time_to_compile = nums[2];
	args->time_to_debug = nums[3];
	args->time_to_refactor = nums[4];
	args->num_compiles_req = nums[5];
	args->dongle_cooldown = nums[6];
	if (strcmp(scheduler, "fifo") == 0)
		args->scheduler = FIFO;
	else if (strcmp(scheduler, "edf") == 0)
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
				"<time_to_burnout> <time_to_compile> <time_to_debug> "
				"<time_to_refactor> <number_of_compiles_required> "
				"<dongle_cooldown> <scheduler>\n"), 0);
	i = 1;
	while (i < 8)
	{
		if (!parse_number(av[i], &nums[i - 1]))
			return (fprintf(stderr, "Error: argument %i must be a "
					"non-negative integer\n", i), 0);
		if (!validate_if_positive(i, nums[i - 1]))
			return (fprintf(stderr, "Error: argument %i must be "
					"positive\n", i), 0);
		i++;
	}
	return (assign_args(args, nums, av[8]));
}
