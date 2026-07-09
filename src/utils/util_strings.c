/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_strings.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:54:20 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/08 14:02:20 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

char	*not_enough_arg(void)
{
	return ("Usage: ./codexion <num_coders> "
		"<time_to_burnout> "
		"<time_to_compile> "
		"<time_to_refactor> "
		"[num_compiles_before_success]\n");
}

char	*must_be(void)
{
	return ("Error: Argument '%s' must be %s\n");
}
