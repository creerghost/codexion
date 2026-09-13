/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_api.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/12 23:30:00 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_API_H
# define DONGLE_API_H

# include <stdbool.h>
# include "structs/dongle.h"

bool	init_dongles(t_dongle **dongles, int count, t_scheduler_mode mode);
void	free_dongles(t_dongle *dongles, int count);
bool	dongle_add_request(t_dongle *dongle, t_request request);
void	dongle_release(t_dongle *dongle, long long release_time,
			long long cooldown);

#endif
