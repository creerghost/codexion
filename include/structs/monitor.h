/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/16 18:34:10 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

# include <pthread.h>
# include <stddef.h>

typedef struct s_context	t_context;
typedef struct s_coder		t_coder;
typedef struct s_scheduler	t_scheduler;

typedef struct s_monitor
{
	pthread_t	thread;
	t_context	*context;
	t_coder		*coders;
	t_scheduler	*scheduler;
	size_t		count;
}	t_monitor;

#endif
