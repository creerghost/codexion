/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_compare.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/23 15:58:53 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/queue_api.h"
#include "queue_internal.h"

static bool	fifo_precedes(const t_request *first, const t_request *second)
{
	if (first->sequence != second->sequence)
		return (first->sequence < second->sequence);
	return (first->coder_id < second->coder_id);
}

static bool	edf_precedes(const t_request *first, const t_request *second)
{
	if (first->deadline != second->deadline)
		return (first->deadline < second->deadline);
	return (fifo_precedes(first, second));
}

bool	request_precedes(const t_request *first,
		const t_request *second, t_scheduler_mode mode)
{
	if (mode == EDF)
		return (edf_precedes(first, second));
	return (fifo_precedes(first, second));
}
