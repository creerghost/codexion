/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:43:52 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/14 12:50:56 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCHEDULER_INTERNAL_H
# define SCHEDULER_INTERNAL_H

# include <stdbool.h>
# include "structs/scheduler.h"

bool	scheduler_try_grant_locked(t_scheduler *scheduler, long long now);

#endif
