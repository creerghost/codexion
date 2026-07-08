/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:54:58 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/08 12:56:56 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** Wrapper for protected printf.
*/
void log_msg(t_sim *sim, int coder_id, char *msg)
{
    pthread_mutex_lock(&(sim->log_mutex));
    printf("%ld %d %s\n", get_time_ms() - sim->start_time, coder_id, msg);
    pthread_mutex_unlock(&(sim->log_mutex));
}