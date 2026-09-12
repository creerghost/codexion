/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 17:13:39 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/12 18:13:27 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/coder.h"
#include "structs/application.h"
#include <bits/pthreadtypes.h>
#include <stdlib.h>
#include <threads.h>

static void	free_coders(int	idx, t_coder *coders)
{
	int	i;

	i = 0;
	while (i < idx)
	{
		pthread_mutex_destroy(&coders[i].mutex);
		pthread_cond_destroy(&coders[i].cond);
		i++;
	}
	free(coders);	
}

static int	init_coder(int id, t_coder *coder,
			t_dongle *left, t_dongle *right)
{
	coder->id = id;
	coder->last_release_time = 0;
	coder->left_dongle = left;
	coder->right_dongle = right;
	if (pthread_mutex_init(&coder->mutex, NULL) != 0)
		return (0);
	if (pthread_cond_init(&coder->cond, NULL) != 0)
		return (0);
	return (1);
}

int	init_coders(int num_coders, t_application *app)
{
	int		idx;
	int		ld_idx;
	int		rd_idx;

	app->coders = (t_coder *)malloc(sizeof(t_coder) * num_coders);
	if (!app->coders)
		return (0);
	idx = 0;
	while (idx < num_coders)
	{
		ld_idx = idx;
		rd_idx = idx % num_coders - 1;
		if (!init_coder(idx, &app->coders[idx],
				&app->dongles[ld_idx], &app->dongles[rd_idx]))
			return (free_coders(idx, app->coders), 0);
		idx++;
	}
	return (1);
}