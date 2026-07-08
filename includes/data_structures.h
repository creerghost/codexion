/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 11:45:28 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/09 01:07:51 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

# include <pthread.h>
# include <stdbool.h>

/* Enum of scheduler algorithms */
typedef enum e_scheduler
{
    FIFO,
    EDF
}               t_scheduler;

/* Parsed arguments */
typedef struct s_args
{
	int num_coders;
	long time_to_burnout;
	long time_to_compile;
	long time_to_debug;
	long time_to_refactor;
	int num_compiles_req;
	long dongle_cooldown;
	t_scheduler scheduler;
}               t_args;

/* struct heap: Min-Heap Priority Queue
*
*   coder_ids: array of coder IDs in heap (1-indexed)
*   keys: priority key for each coder (timestamp for FIFO, deadline for EDF)
*   size: current number of elements in heap
*   capacity: max number of elements in heap (number of coders)
*/
typedef struct s_heap
{
	int		*coder_ids;
	long	*keys;
	int		size;
	int		capacity;
}	t_heap;

/* struct dongle: Shared Resource
*
*   mutex: protects this dongle's state
*   cond: coders wait here for this dongle
*   held: 1 if currently held, 0 if free
*   release_time: timestamp when last released (for cooldown)
*   heapq: pending requests sorted by scheduler policy
*/
typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	bool			held;
	long			release_time;
	t_heap			heapq;
}	t_dongle;

/* struct coder: Per-Thread Data
* 
*   id: coder identifier (1-indexed for display)
*   compile_count: number of times this coder has compiled
*   last_compile_start: timestamp of last compile start (0 = sim start)
*   left_dongle: index into ctx->dongles for left dongle
*   right_dongle: index into ctx->dongles for right dongle
*   first_dongle: index of first dongle to acquire (min of left/right)
*   second_dongle: index of second dongle to acquire (max of left/right)
*   thread_id: pthread identifier for this coder's thread
*   mutex: protects this coder's state from data races with the monitor
*   ctx: back-pointer to the global simulation context
*/
typedef struct s_coder
{
	int				id;
	int				compile_count;
	long			last_compile_start;
	int				left_dongle;
	int				right_dongle;
	int				first_dongle;
	int				second_dongle;
	pthread_t		thread_id;
	pthread_mutex_t	mutex;
	struct s_context	*ctx;
}	t_coder;

/* struct context: Simulation Context
*
*   args:	pointer to the args struct
*   coders: array of all coders
*   dongles: array of all dongles
*   log_mutex: protects log output to prevent interleaving
*   sim_mutex: protects shared simulation state variables
*   done_cond: condition variable to signal simulation end
*   active_coders: number of currently running coder threads
*   start_time: simulation start timestamp in ms
*/
typedef struct s_context
{
	t_args			*args;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	sim_mutex;
	pthread_cond_t	done_cond;
	int				active_coders;
	long			start_time;
}	t_context;

#endif