/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 17:10:57 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/09 17:37:02 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static bool	grab_two_dongles(t_coder *coder, t_dongle *d1, t_dongle *d2)
{
	if (!grab_dongle(coder, d1))
		return (false);
	if (!grab_dongle(coder, d2))
		return (release_dongle(d1), false);
	return (true);
}

static void	compile(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
	coder->compile_count++;
	coder->last_compile_start = get_time_ms();
	pthread_mutex_unlock(&coder->mutex);
	log_msg(coder->ctx, coder->id, "is compiling");
	ft_sleep(coder->ctx->args->time_to_compile, coder->ctx);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (is_sim_running(coder->ctx))
	{
		if (!grab_two_dongles(coder, coder->ctx->dongles + coder->first_dongle,
				coder->ctx->dongles + coder->second_dongle))
			break ;
		compile(coder);
		release_dongle(coder->ctx->dongles + coder->first_dongle);
		release_dongle(coder->ctx->dongles + coder->second_dongle);
		log_msg(coder->ctx, coder->id, "is debugging");
		ft_sleep(coder->ctx->args->time_to_debug, coder->ctx);
		log_msg(coder->ctx, coder->id, "is refactoring");
		ft_sleep(coder->ctx->args->time_to_refactor, coder->ctx);
	}
	return (NULL);
}
