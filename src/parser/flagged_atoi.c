/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagged_atoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 00:42:59 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/09 00:58:10 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	atoi_flagged(const char *str, int *result)
{
	long	num;

	num = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			return (0);
	if (!*str || (*str < '0' || *str > '9'))
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		num = num * 10 + (*str - '0');
		if (num > INT_MAX || num < INT_MIN)
			return (0);
		str++;
	}
	*result = num;
	return (1);
}
