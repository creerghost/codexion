/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 16:55:08 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/12 17:56:52 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "dongle.h"
#include <bits/pthreadtypes.h>
# include <pthread.h>

typedef struct  	s_coder
{
	int         	id;
	long long   	last_release_time;
	
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	pthread_t   	thread;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	   
}               	t_coder;

#endif