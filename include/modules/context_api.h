/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_api.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/12 23:30:00 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_API_H
# define CONTEXT_API_H

# include <stdbool.h>
# include "structs/args.h"
# include "structs/context.h"

bool	init_context(t_context *context, const t_args *args);
bool	context_is_running(t_context *context);
void	stop_context(t_context *context);
void	free_context(t_context *context);

#endif
