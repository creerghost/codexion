/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:55:14 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/08 13:23:07 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CODEXION_H
# define CODEXION_H

# include "data_structures.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

/* time_utils.c */
long get_time_ms(void);
void ft_sleep(long duration_ms, t_sim *sim);
long elapsed_ms(t_sim *sim);

/* logging.c */
void log_msg(t_sim *sim, int coder_id, char *msg);

/* atoi_codex.c*/
int	uatol(const char *str, int *result);

/* util_strings.c */
char	*not_enough_arg(void);
char    *must_be(void);

/* parser.c */
int parse_args(int ac, char **av, t_sim *sim);

#endif