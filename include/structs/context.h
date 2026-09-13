/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/12 23:30:00 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include <pthread.h>

typedef struct s_args	t_args;

typedef struct s_context
{
	const t_args		*args;
	long long			start_time;
	int					is_running;
	pthread_mutex_t		state_mutex;
	pthread_mutex_t		log_mutex;
}	t_context;

#endif
