/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 22:16:12 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "modules/parser_api.h"

static bool	validate_if_positive(size_t index, int number)
{
	if (index == 1 || index == 6)
		return (number > 0);
	return (number >= 0);
}

static bool	assign_args(t_args *args, const int *numbers,
		const char *scheduler)
{
	args->num_coders = numbers[0];
	args->time_to_burnout = numbers[1];
	args->time_to_compile = numbers[2];
	args->time_to_debug = numbers[3];
	args->time_to_refactor = numbers[4];
	args->num_compiles_req = numbers[5];
	args->dongle_cooldown = numbers[6];
	if (strcmp(scheduler, "fifo") == 0)
		args->scheduler = FIFO;
	else if (strcmp(scheduler, "edf") == 0)
		args->scheduler = EDF;
	else
		return (fprintf(stderr, "Error: scheduler must be \"fifo\" or "
				"\"edf\"\n"), false);
	return (true);
}

bool	parse_args(int ac, char **av, t_args *args)
{
	size_t	index;
	int		numbers[7];

	if (ac != 9)
		return (printf("Usage: ./codexion <number_of_coders> "
				"<time_to_burnout> <time_to_compile> <time_to_debug> "
				"<time_to_refactor> <number_of_compiles_required> "
				"<dongle_cooldown> <scheduler>\n"), false);
	index = 1;
	while (index < 8)
	{
		if (!parse_number(av[index], &numbers[index - 1]))
			return (fprintf(stderr, "Error: argument %zu must be a "
					"non-negative integer\n", index), false);
		if (!validate_if_positive(index, numbers[index - 1]))
			return (fprintf(stderr, "Error: argument %zu must be "
					"positive\n", index), false);
		index++;
	}
	return (assign_args(args, numbers, av[8]));
}
