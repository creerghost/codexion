/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_api.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/12 23:30:00 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_API_H
# define TIME_API_H

# include "structs/context.h"

long long	current_time_ms(void);
long long	simulation_time_ms(t_context *context);
void		interruptible_sleep(t_context *context, long long duration);

#endif
