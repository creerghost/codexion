/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:27:04 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/08 12:42:31 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structures.h"
#include <sys/time.h>

/*
** Wrapper of gettimeofday.
** Returns the current time in milliseconds.
*/
long get_time_ms(void)
{
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/*
** Precise sleep using usleep() + busy-wait tail.
** Sleeps for the given duration in milliseconds, waiting for the simulation
** to end.
*/
void ft_sleep(long duration_ms, t_context *ctx)
{
  long target;

  target = get_time_ms() + duration_ms;
  while (get_time_ms() < target)
  {
    pthread_mutex_lock(&ctx->sim_mutex);
    pthread_cond_wait(&ctx->done_cond, &ctx->sim_mutex);
    pthread_mutex_unlock(&ctx->sim_mutex);
  }
}

/*
** Returns the time elapsed since the simulation started.
*/
long elapsed_ms(t_context *ctx)
{
    return (get_time_ms() - ctx->start_time);
}
