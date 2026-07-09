/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:54:20 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/08 14:02:20 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_context	ctx;

	if (!init_context(argc, argv, &ctx))
		return (1);
	printf("Initialized %d coders and %d dongles\n", ctx.args->num_coders,
		ctx.args->num_coders);
	free_context(&ctx);
	return (0);
}
