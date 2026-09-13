/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 21:46:56 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/coder_api.h"
#include "modules/gate_api.h"
#include "structs/context.h"
#include "structs/dongle.h"
#include <stdlib.h>

void	free_coders(t_coder *coders, int count)
{
	int	idx;

	if (coders == NULL)
		return ;
	idx = 0;
	while (idx < count)
	{
		free_gate(&coders[idx].gate);
		pthread_mutex_destroy(&coders[idx].data_mutex);
		idx++;
	}
	free(coders);
}

static bool	init_coder(t_coder *coder, t_context *context,
		t_dongle *left_dongle, t_dongle *right_dongle)
{
	coder->context = context;
	coder->left_dongle = left_dongle;
	coder->right_dongle = right_dongle;
	coder->last_compile_start = context->start_time;
	coder->compiles_done = 0;
	if (pthread_mutex_init(&coder->data_mutex, NULL))
		return (false);
	if (!init_gate(&coder->gate))
		return (pthread_mutex_destroy(&coder->data_mutex), false);
	return (true);
}

bool	init_coders(t_coder **coders, int count, t_context *context,
		t_dongle *dongles)
{
	int			idx;
	t_coder		*new_coders;

	if (coders == NULL || count <= 0 || context == NULL || dongles == NULL)
		return (false);
	new_coders = (t_coder *)malloc(sizeof(t_coder) * count);
	if (new_coders == NULL)
		return (false);
	idx = 0;
	while (idx < count)
	{
		new_coders[idx].id = idx + 1;
		if (!init_coder(&new_coders[idx], context, &dongles[idx],
				&dongles[(idx + 1) % count]))
			return (free_coders(new_coders, idx), false);
		idx++;
	}
	*coders = new_coders;
	return (true);
}
