/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/13 17:55:21 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "modules/parser_api.h"

bool	parse_number(const char *str, int *result)
{
	long	num;

	num = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			return (false);
	if (!*str || (*str < '0' || *str > '9'))
		return (false);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		num = num * 10 + (*str - '0');
		if (num > INT_MAX || num < INT_MIN)
			return (false);
		str++;
	}
	*result = num;
	return (false);
}
