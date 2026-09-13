/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 14:41:07 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 14:43:09 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_INTERNAL_H
# define QUEUE_INTERNAL_H

# include <stdbool.h>
# include "structs/queue.h"

bool	request_precedes(const t_request *first,
			const t_request *second, t_scheduler_mode mode);

#endif
