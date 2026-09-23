/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_api.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/12 23:30:00 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_API_H
# define CODER_API_H

# include <stdbool.h>
# include <stddef.h>
# include "structs/coder.h"

bool		init_coders(t_coder **coders, size_t count, t_context *context,
				t_dongle *dongles);
void		free_coders(t_coder *coders, size_t count);
void		*coder_routine(void *argument);
long long	coder_last_compile(t_coder *coder);
int			coder_compile_count(t_coder *coder);
void		coder_mark_compile_start(t_coder *coder, long long start_time);

#endif
