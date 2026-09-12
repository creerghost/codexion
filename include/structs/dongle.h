/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 16:59:39 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/12 18:07:26 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DONGLE_H
# define CODER_H

#include "structs/queue.h"
# include <pthread.h>

typedef struct  	s_dongle
{
	long long		last_release_time;
	pthread_mutex_t	mutex;
	t_queue			queue;
}               	t_dongle;

#endif