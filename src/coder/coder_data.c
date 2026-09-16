/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/16 12:57:38 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/coder_api.h"

int	coder_compile_count(t_coder *coder)
{
	int	compiles_done;

	if (!coder)
		return (-1);
	pthread_mutex_lock(&coder->data_mutex);
	compiles_done = coder->compiles_done;
	pthread_mutex_unlock(&coder->data_mutex);
	return (compiles_done);
}

long long	coder_last_compile(t_coder *coder)
{
	long long	last_compile;

	if (!coder)
		return (-1);
	pthread_mutex_lock(&coder->data_mutex);
	last_compile = coder->last_compile_start;
	pthread_mutex_unlock(&coder->data_mutex);
	return (last_compile);
}
