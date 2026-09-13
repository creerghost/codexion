/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_api.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 14:11:49 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_API_H
# define PARSER_API_H

# include "structs/args.h"
# include <stdbool.h>

bool	parse_number(const char *str, int *result);
bool	arse_args(int ac, char **av, t_args *args);

#endif
