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

/**
 * @brief Returns the minimum of two integers.
 * 
 * @param a First integer.
 * @param b Second integer.
 * @return The minimum of the two integers.
 */
int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

/**
 * @brief Returns the maximum of two integers.
 * 
 * @param a First integer.
 * @param b Second integer.
 * @return The maximum of the two integers.
 */
int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

/**
 * @brief Allocates memory for an array and initializes to zero.
 * 
 * @param size The size of the allocation in bytes.
 * @return Pointer to the allocated memory, or NULL on failure.
 */
void	*ft_calloc(size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(size);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, size);
	return (ptr);
}

/**
 * @brief Thread-safe check if the simulation is still running.
 * 
 * @param ctx Pointer to the simulation context.
 * @return true if running, false if stopped.
 */
bool	is_sim_running(t_context *ctx)
{
	bool	status;

	pthread_mutex_lock(&ctx->sim_mutex);
	status = ctx->is_running;
	pthread_mutex_unlock(&ctx->sim_mutex);
	return (status);
}
