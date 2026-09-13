/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:30:00 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/12 23:30:00 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include <pthread.h>
# include "structs/gate.h"

typedef struct s_context	t_context;
typedef struct s_dongle		t_dongle;

typedef struct s_coder
{
	int				id;
	pthread_t		thread;
	t_context		*context;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	t_gate			gate;
	pthread_mutex_t	data_mutex;
	long long		last_compile_start;
	int				compiles_done;
}	t_coder;

#endif
