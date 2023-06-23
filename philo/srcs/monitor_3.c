/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noa <noa@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:18:04 by noa               #+#    #+#             */
/*   Updated: 2023/06/21 20:56:53 by noa              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "../includes/utils.h"
#include "../includes/simulation.h"
#include "../includes/philo.h"

void	set_simulation_state(t_simulation *simulation, t_simulation_state state)
{
	pthread_mutex_lock(&simulation->mut);
	simulation->state = state;
	pthread_mutex_unlock(&simulation->mut);
}

t_simulation_state	get_simulation_state(t_simulation *simulation)
{
	t_simulation_state	state;

	pthread_mutex_lock(&simulation->mut);
	state = simulation->state;
	pthread_mutex_unlock(&simulation->mut);
	return (state);
}

bool	start_monitor(t_monitor	*monitor)
{
	int32_t	i;
	int32_t	nb_philo;

	nb_philo = monitor->simulation.params.nb_philo;
	i = -1;
	while (++i < nb_philo)
	{
		if (pthread_create(&monitor->threads[i], NULL, philo_thread, \
			&monitor->philos[i]))
		{
			set_simulation_state(&monitor->simulation, STOP);
			while (--i >= 0)
				pthread_join(monitor->threads[i], NULL);
			return (false);
		}
	}
	i = -1;
	monitor->simulation.start_time = get_current_time_(&monitor->simulation);
	while (++i < nb_philo)
		monitor->philos[i].last_meal_time = monitor->simulation.start_time;
	set_simulation_state(&monitor->simulation, START);
	return (true);
}

void	stop_monitor(t_monitor *monitor)
{
	int32_t	i;
	int32_t	nb_philo;

	nb_philo = monitor->simulation.params.nb_philo;
	set_simulation_state(&monitor->simulation, STOP);
	i = -1;
	while (++i < nb_philo)
	{
		pthread_join(monitor->threads[i], NULL);
	}
}

bool	one_dead(t_monitor *monitor)
{
	int32_t	nb_philo;
	int32_t	i;

	nb_philo = monitor->simulation.params.nb_philo;
	i = -1;
	while (++i < nb_philo)
	{
		if (monitor->snapshots[i].state == DEAD)
			return (true);
	}
	return (false);
}
