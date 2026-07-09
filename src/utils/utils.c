/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:54:20 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/08 14:02:20 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/* Returns the minimum of two integers */
int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

/* Returns the maximum of two integers */
int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

/* Allocates memory for an array of elements and initializes them to zero. */
void	*ft_calloc(size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(size);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, size);
	return (ptr);
}

bool	is_sim_running(t_context *ctx)
{
	bool	status;

	pthread_mutex_lock(&ctx->sim_mutex);
	status = ctx->is_running;
	pthread_mutex_unlock(&ctx->sim_mutex);
	return (status);
}
