/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 23:54:33 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/08 23:55:32 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "structs/args.h"
#include "parse.h"

static void	test_valid_fifo_populates_args(void)
{
	t_args	args;
	char	*str[9];

	str[0] = "./codexion";
	str[1] = "3";
	str[2] = "800";
	str[3] = "200";
	str[4] = "200";
	str[5] = "50";
	str[6] = "2";
	str[7] = "10";
	str[8] = "fifo";
	assert(parse_args(9, str, &args) == 1);
	assert(args.num_coders == 3);
	assert(args.time_to_burnout == 800);
	assert(args.time_to_compile == 200);
	assert(args.time_to_debug == 200);
	assert(args.time_to_refactor == 50);
	assert(args.num_compiles_req == 2);
	assert(args.dongle_cooldown == 10);
	assert(args.scheduler == FIFO);
}

static void	test_valid_edf_sets_scheduler(void)
{
	t_args	args;
	char	*str[9];

	str[0] = "./codexion";
	str[1] = "2";
	str[2] = "800";
	str[3] = "200";
	str[4] = "200";
	str[5] = "50";
	str[6] = "1";
	str[7] = "0";
	str[8] = "edf";
	assert(parse_args(9, str, &args) == 1);
	assert(args.scheduler == EDF);
}

static void	test_rejects_invalid_args(void)
{
	t_args	args;
	char	*str[9];

	str[0] = "./codexion";
	str[1] = "3";
	str[2] = "800";
	str[3] = "200";
	str[4] = "200";
	str[5] = "50";
	str[6] = "2";
	str[7] = "10";
	str[8] = "fifo";
	assert(parse_args(8, str, &args) == 0);
	str[1] = "abc";
	assert(parse_args(9, str, &args) == 0);
	str[1] = "-5";
	assert(parse_args(9, str, &args) == 0);
	str[1] = "0";
	assert(parse_args(9, str, &args) == 0);
	str[1] = "3";
	str[6] = "0";
	assert(parse_args(9, str, &args) == 0);
	str[6] = "2";
	str[8] = "rand";
	assert(parse_args(9, str, &args) == 0);
}

int	main(void)
{
	test_valid_fifo_populates_args();
	test_valid_edf_sets_scheduler();
	test_rejects_invalid_args();
	return (0);
}
