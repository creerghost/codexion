/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/12 23:30:00 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCHEDULER_H
# define SCHEDULER_H

# include <pthread.h>

typedef struct s_context	t_context;
typedef struct s_coder		t_coder;
typedef struct s_dongle		t_dongle;

typedef struct s_scheduler
{
	pthread_t		thread;
	t_context		*context;
	t_coder			*coders;
	t_dongle		*dongles;
	int				count;
	pthread_mutex_t	mutex;
	pthread_cond_t	condition;
	int				notified;
}	t_scheduler;

#endif
