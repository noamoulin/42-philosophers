/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noa <noa@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:17:43 by noa               #+#    #+#             */
/*   Updated: 2023/06/23 13:24:24 by noa              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/simulation.h"
#include "../includes/utils.h"

static void	*ask_time(void *data)
{
	t_simulation	*simulation;
	uint64_t		time;

	simulation = (t_simulation *)data;
	while (get_simulation_state(simulation) != STOP)
	{
		time = get_time_ms();
		pthread_mutex_lock(&simulation->mut);
		simulation->current_time = time;
		pthread_mutex_unlock(&simulation->mut);
		usleep(300);
	}
	return (NULL);
}

static void	monitor_routine(t_monitor *monitor)
{
	maj_snaps(monitor);
	give_eat_permission(monitor);
	if (one_dead(monitor) || all_eat_enought(monitor))
		set_simulation_state(&monitor->simulation, STOP);
	usleep(300);
}

int	main(int ac, char **av)
{
	t_monitor	monitor;
	t_params	params;
	pthread_t	timer;

	if (!set_params(&params, ac, av))
	{
		printf("Error Wrong Input\n");
		return (EXIT_FAILURE);
	}
	if (!init_monitor(&monitor, params))
		return (EXIT_FAILURE);
	take_current_time(&monitor.simulation);
	if (!start_monitor(&monitor) || \
		pthread_create(&timer, NULL, ask_time, &monitor.simulation))
	{
		destroy_monitor(&monitor);
		return (EXIT_FAILURE);
	}
	while (get_simulation_state(&monitor.simulation) != STOP)
		monitor_routine(&monitor);
	stop_monitor(&monitor);
	pthread_join(timer, NULL);
	destroy_monitor(&monitor);
	return (EXIT_SUCCESS);
}
