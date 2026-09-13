/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   application_api.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/12 23:30:00 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLICATION_API_H
# define APPLICATION_API_H

# include <stdbool.h>
# include "structs/application.h"

bool	init_application(t_application *app, int ac, char **av);
bool	run_application(t_application *app);
void	free_application(t_application *app);

#endif
