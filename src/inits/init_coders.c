/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:20:02 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/09 00:46:42 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void free_coders(t_sim *sim, unsigned int amount)
{
    unsigned int    i;

    i = 0;
    if (!sim->coders)
        return ;
    while (i < amount)
        pthread_mutex_destroy(&sim->coders[i++].mutex);
    free(sim->coders);
    sim->coders = NULL;
}

static bool init_single_coder(t_sim *sim, int i)
{
    sim->coders[i].id = i + 1;
    sim->coders[i].compile_count = 0;
    sim->coders[i].last_compile_start = 0;
    sim->coders[i].left_dongle = i;
    sim->coders[i].right_dongle = (i + 1) % sim->num_coders;
    sim->coders[i].first_dongle = ft_min(sim->coders[i].left_dongle, sim->coders[i].right_dongle);
    sim->coders[i].second_dongle = ft_max(sim->coders[i].left_dongle, sim->coders[i].right_dongle);
    sim->coders[i].sim = sim;
    if (pthread_mutex_init(&sim->coders[i].mutex, NULL) != 0)
        return (false);
    return (true);
}

bool init_coders(t_sim *sim)
{
    int i;

    sim->coders = (t_coder *)ft_calloc(sim->num_coders * sizeof(t_coder));
    if (!sim->coders)
        return (false);
    i = 0;
    while (i < sim->num_coders)
        if (!init_single_coder(sim, i++))
            return (free_coders(sim, i), false);
    return (true);
}