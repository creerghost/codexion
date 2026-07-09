/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:54:20 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/08 14:02:20 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include "data_structures.h"
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/* utils.c */
void	*ft_calloc(size_t size);
int		ft_min(int a, int b);
int		ft_max(int a, int b);

/* time_utils.c */
bool	is_sim_running(t_context *ctx);
long	get_time_ms(void);
void	ft_sleep(long duration_ms, t_context *ctx);
long	elapsed_ms(t_context *ctx);

/* logging.c */
void	log_msg(t_context *ctx, int coder_id, char *msg);

/* atoi_codex.c*/
int		uatol(const char *str, int *result);

/* util_strings.c */
char	*not_enough_arg(void);
char	*must_be(void);

/* parser.c */
int		parse_args(int ac, char **av, t_context *ctx);

/* heap.c */
bool	ft_heap_new(t_heap *heap, int capacity);
bool	ft_heappush(t_heap *heap, int coder_id, long key);
bool	ft_heappop(t_heap *heap, int *coder_id);
int		ft_heappeek(t_heap *heap);
void	ft_heapfree(t_heap *heap);

/* heap_utils.c */
void	bubble_down(t_heap *heap);
void	bubble_up(t_heap *heap, int current);

/* init_dongles.c */
bool	init_dongles(t_context *ctx);
void	free_dongles(t_context *ctx, unsigned int amount);

/* init_coders.c*/
bool	init_coders(t_context *ctx);
void	free_coders(t_context *ctx, unsigned int amount);

/* init_context.c */
bool	init_context(int argc, char **argv, t_context *ctx);
void	free_context(t_context *ctx);

/* dongle.c */
bool	grab_dongle(t_coder *coder, t_dongle *dongle);
void	release_dongle(t_dongle *dongle);

/* routine.c */
void	*coder_routine(void *arg);

/* monitor.c */
void	*monitor_routine(void *arg);

#endif
