/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 13:14:27 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/08 13:37:01 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

char	*not_enough_arg(void)
{
	return ("Usage: ./coders <num_coders> "
		"<time_to_burnout> <time_to_compile> "
		"<time_to_debug> <time_to_refactor> "
		"<num_compiles_req> <dongle_cooldown> "
		"<scheduler> (FIFO or EDF)\n");
}

char    *must_be(void)
{
    return ("Error: Argument '%s' must be %s\n");
}