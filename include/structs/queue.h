/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 01:37:30 by vlnikola          #+#    #+#             */
/*   Updated: 2026/09/12 18:27:17 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include "args.h"
// sequence is poryadok
typedef struct			s_request
{
	int					coder_id;
	long long			deadline;
	unsigned long long	seq;
}						t_request;

typedef struct			s_queue
{
    t_request			*heap;
    int					size;
    int					capacity;
    unsigned long long	next_seq;
    t_scheduler			scheduler;
}						t_queue;

#endif
