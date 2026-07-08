/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 23:54:54 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/09 00:18:09 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void free_dongles(t_sim *sim, unsigned int amount)
{
    unsigned int    i;

    i = 0;
    if (!sim->dongles)
        return ;
    while (i < amount)
    {
        ft_heapfree(&sim->dongles[i].heapq);
        pthread_mutex_destroy(&sim->dongles[i].mutex);
        pthread_cond_destroy(&sim->dongles[i].cond);
        i++;
    }
    free(sim->dongles);
    sim->dongles = NULL;
}

static bool init_single_dongle(t_sim *sim, int i)
{
    sim->dongles[i].held = false;
    sim->dongles[i].release_time = 0;
    if (!ft_heap_new(&sim->dongles[i].heapq, sim->num_coders))
        return (false);
    if (pthread_mutex_init(&sim->dongles[i].mutex, NULL) != 0)
        return (ft_heapfree(&sim->dongles[i].heapq), false);
    if (pthread_cond_init(&sim->dongles[i].cond, NULL) != 0)
        return (pthread_mutex_destroy(&sim->dongles[i].mutex),
                ft_heapfree(&sim->dongles[i].heapq), false);
    return (true);
}

bool init_dongles(t_sim *sim)
{
    int i;

    sim->dongles = (t_dongle *)malloc(sim->num_coders * sizeof(t_dongle));
    if (!sim->dongles)
        return (false);
    i = 0;
    while (i < sim->num_coders)
        if (!init_single_dongle(sim, i++))
            return (free_dongles(sim, i), false);
    return (true);
}