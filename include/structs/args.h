/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 23:54:33 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/08 23:55:32 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H

typedef enum e_scheduler
{
	FIFO,
	EDF
}						t_scheduler;

typedef struct s_args
{
	int					num_coders;
	long				time_to_burnout;
	long				time_to_compile;
	long				time_to_debug;
	long				time_to_refactor;
	int					num_compiles_req;
	long				dongle_cooldown;
	t_scheduler			scheduler;
}						t_args;

#endif