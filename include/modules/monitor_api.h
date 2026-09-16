/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_api.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/16 18:35:12 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_API_H
# define MONITOR_API_H

# include <stddef.h>
# include "structs/monitor.h"

void	init_monitor(t_monitor *monitor, t_scheduler *scheduler);
void	*monitor_routine(void *argument);

#endif
