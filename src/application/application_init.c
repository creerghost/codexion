/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   application_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 14:16:16 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "modules/application_api.h"
#include "modules/parser_api.h"

bool	init_application(t_application *app, int ac, char **av)
{
	memset(app, 0, sizeof(*app));
	if (!parse_args(ac, av, &app->args))
		return (false);
	
}
