/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noa <noa@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:17:49 by noa               #+#    #+#             */
/*   Updated: 2023/06/17 16:40:22 by noa              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "../includes/utils.h"
#include "../includes/simulation.h"
#include "../includes/philo.h"

bool	alloc_monitor(t_monitor *monitor)
{
	int32_t	philo_number;

	philo_number = monitor->simulation.params.nb_philo;
	monitor->threads = malloc(sizeof(pthread_t) * philo_number);
	monitor->philos = malloc(sizeof(t_philo) * philo_number);
	monitor->snapshots = malloc(sizeof(t_philo_snapshot) * philo_number);
	monitor->forks = malloc(sizeof(pthread_mutex_t) * philo_number);
	if (!monitor->threads || !monitor->philos || !monitor->snapshots || \
		!monitor->forks)
	{
		free_monitor(monitor);
		return (false);
	}
	return (true);
}

bool	init_monitor_philos(t_monitor *monitor)
{
	int32_t	i;
	int32_t	nb_philo;

	nb_philo = monitor->simulation.params.nb_philo;
	i = -1;
	while (++i < nb_philo)
	{
		if (!init_philo(&monitor->philos[i], i, monitor))
		{
			while (--i >= 0)
				destroy_philo(&monitor->philos[i]);
			return (false);
		}
	}
	return (true);
}

bool	init_monitor_mutex(t_monitor *monitor)
{
	int32_t	i;
	int32_t	nb_philo;

	nb_philo = monitor->simulation.params.nb_philo;
	i = -1;
	while (++i < nb_philo)
	{
		if (pthread_mutex_init(&monitor->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&monitor->forks[i]);
			return (false);
		}
	}
	return (true);
}

bool	init_simulation(t_simulation *simulation, t_params params)
{
	simulation->params = params;
	if (pthread_mutex_init(&simulation->mut, NULL))
		return (false);
	if (pthread_mutex_init(&simulation->speaker, NULL))
	{
		pthread_mutex_destroy(&simulation->mut);
		return (false);
	}
	simulation->state = WAIT;
	return (true);
}

void	destroy_simulation(t_simulation *simulation)
{
	simulation->state = STOP;
	pthread_mutex_destroy(&simulation->mut);
	pthread_mutex_destroy(&simulation->speaker);
}
