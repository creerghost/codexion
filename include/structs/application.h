/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   application.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 18:03:18 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLICATION_H
# define APPLICATION_H

# include <stdbool.h>
# include <stddef.h>
# include "structs/args.h"
# include "structs/context.h"
# include "structs/coder.h"
# include "structs/dongle.h"
# include "structs/monitor.h"
# include "structs/scheduler.h"

typedef struct s_application
{
	t_args			args;
	t_context		context;
	t_coder			*coders;
	t_dongle		*dongles;
	t_scheduler		scheduler;
	t_monitor		monitor;
	bool			context_initialized;
	size_t			coders_initialized;
	size_t			dongles_initialized;
	size_t			coder_threads_created;
	bool			scheduler_initialized;
	bool			scheduler_thread_created;
	bool			monitor_thread_created;
}	t_application;

#endif
