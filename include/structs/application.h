/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   application.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 17:06:21 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/12 18:32:41 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLICATION_H
# define APPLICATION_H

# include <pthread.h>
# include "coder.h"
# include "dongle.h"
# include "monitor.h"
# include "context.h"


typedef struct	s_application
{
	t_coder		*coders;
	t_dongle	*dongles;
	t_monitor	monitor;
	t_context	context;
}				t_application;

#endif