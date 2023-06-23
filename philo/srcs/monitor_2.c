/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noa <noa@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:17:57 by noa               #+#    #+#             */
/*   Updated: 2023/06/17 15:59:01 by noa              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "../includes/utils.h"
#include "../includes/simulation.h"
#include "../includes/philo.h"

void	free_monitor(t_monitor *monitor)
{
	free(monitor->threads);
	free(monitor->philos);
	free(monitor->snapshots);
	free(monitor->forks);
}

void	destroy_monitor_mutex(t_monitor *monitor)
{
	int32_t	i;
	int32_t	nb_philo;

	nb_philo = monitor->simulation.params.nb_philo;
	i = -1;
	while (++i < nb_philo)
		pthread_mutex_destroy(&monitor->forks[i]);
}

bool	init_monitor(t_monitor *monitor, t_params params)
{
	if (!init_simulation(&monitor->simulation, params))
		return (false);
	if (!alloc_monitor(monitor))
	{
		free_monitor(monitor);
		return (false);
	}
	if (!init_monitor_mutex(monitor))
	{
		destroy_simulation(&monitor->simulation);
		free_monitor(monitor);
		return (false);
	}
	if (!init_monitor_philos(monitor))
	{
		destroy_simulation(&monitor->simulation);
		destroy_monitor_mutex(monitor);
		free_monitor(monitor);
		return (false);
	}
	return (true);
}

void	destroy_monitor(t_monitor *monitor)
{
	destroy_monitor_mutex(monitor);
	free_monitor(monitor);
	destroy_simulation(&monitor->simulation);
}
