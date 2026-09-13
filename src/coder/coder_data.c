/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 22:41:17 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/coder_api.h"

int	coder_compile_count(t_coder *coder)
{
	int	compiles_done;

	if (!coder)
		return (-1);
	pthread_mutex_lock(&coder->data_mutex);
	compiles_done = coder->compiles_done;
	pthread_mutex_unlock(&coder->data_mutex);
	return (compiles_done);
}
