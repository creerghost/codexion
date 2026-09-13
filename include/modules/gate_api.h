/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gate_api.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/12 23:30:00 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GATE_API_H
# define GATE_API_H

# include <stdbool.h>
# include "structs/gate.h"

bool	init_gate(t_gate *gate);
void	gate_wait(t_gate *gate);
void	gate_open(t_gate *gate);
void	free_gate(t_gate *gate);

#endif
