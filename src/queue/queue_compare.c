/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_compare.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 15:06:50 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/queue_api.h"

bool	request_precedes(const t_request *first,
			const t_request *second, t_scheduler_mode mode)
{
	if (mode == EDF && first->deadline != second->deadline)
		return (first->deadline < second->deadline);
	if (first->sequence != second->sequence)
		return (first->sequence < second->sequence);
	return (first->coder_id < second->coder_id);
}
