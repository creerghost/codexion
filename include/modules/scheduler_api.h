/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_api.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/16 18:35:02 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCHEDULER_API_H
# define SCHEDULER_API_H

# include <stdbool.h>
# include "structs/scheduler.h"

bool	init_scheduler(t_scheduler *scheduler, t_context *context,
			t_coder *coders, t_dongle *dongles);
bool	scheduler_request(t_scheduler *scheduler, t_coder *coder);
void	scheduler_notify(t_scheduler *scheduler);
void	*scheduler_routine(void *argument);
void	free_scheduler(t_scheduler *scheduler);

#endif
