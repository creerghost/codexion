/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gate.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 18:40:12 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/gate_api.h"

bool	init_gate(t_gate *gate)
{
	if (gate == NULL)
		return (false);
	gate->ready = 0;
	if (pthread_mutex_init(&gate->mutex, NULL))
		return (false);
	if (pthread_cond_init(&gate->condition, NULL))
		return (pthread_mutex_destroy(&gate->mutex), false);
	return (true);
}

void	gate_wait(t_gate *gate)
{
	pthread_mutex_lock(&gate->mutex);
	while (gate->ready == 0)
		pthread_cond_wait(&gate->condition, &gate->mutex);
	gate->ready = 0;
	pthread_mutex_unlock(&gate->mutex);
}

void	gate_open(t_gate *gate)
{
	pthread_mutex_lock(&gate->mutex);
	gate->ready = 1;
	pthread_cond_signal(&gate->condition);
	pthread_mutex_unlock(&gate->mutex);
}

void	free_gate(t_gate *gate)
{
	pthread_cond_destroy(&gate->condition);
	pthread_mutex_destroy(&gate->mutex);
}
