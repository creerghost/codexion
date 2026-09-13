/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   application.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/12 23:30:00 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLICATION_H
# define APPLICATION_H

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
	int				coders_initialized;
	int				dongles_initialized;
	int				coder_threads_created;
	int				scheduler_thread_created;
	int				monitor_thread_created;
}	t_application;

#endif
