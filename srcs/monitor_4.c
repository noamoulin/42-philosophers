/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomoulin <nomoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:18:08 by noa               #+#    #+#             */
/*   Updated: 2023/06/21 15:18:07 by nomoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "../includes/utils.h"
#include "../includes/simulation.h"
#include "../includes/philo.h"

bool	all_eat_enought(t_monitor *monitor)
{
	int32_t	nb_philo;
	int32_t	i;

	if (monitor->simulation.params.meal_number < 0)
		return (false);
	nb_philo = monitor->simulation.params.nb_philo;
	i = -1;
	while (++i < nb_philo)
	{
		if (monitor->snapshots[i].meal_number < \
			monitor->simulation.params.meal_number)
			return (false);
	}
	return (true);
}

void	maj_snaps(t_monitor *monitor)
{
	int32_t	nb_philo;
	int32_t	i;

	nb_philo = monitor->simulation.params.nb_philo;
	i = -1;
	while (++i < nb_philo)
		monitor->snapshots[i] = get_philo_snapshot(&monitor->philos[i]);
}

void	give_eat_permission(t_monitor *monitor)
{
	t_philo_snapshot	*snap;
	int32_t				nb_philo;
	int32_t				left_id;
	int32_t				right_id;
	int32_t				i;

	nb_philo = monitor->simulation.params.nb_philo;
	if (nb_philo < 2)
		return ;
	snap = monitor->snapshots;
	i = -1;
	while (++i < nb_philo)
	{
		left_id = (i + nb_philo - i) % nb_philo;
		right_id = (i + 1) % nb_philo;
		if ((snap[i].state == THINKING || snap[i].state == STANDBY) && \
			!snap[i].eat_permission && !snap[left_id].eat_permission && \
				!snap[right_id].eat_permission && snap[i].last_meal_time <= \
					snap[left_id].last_meal_time && snap[i].last_meal_time <= \
						snap[right_id].last_meal_time)
		{
			snap[i].eat_permission = true;
			allow_eat(&monitor->philos[i]);
		}
	}
}

void	take_current_time(t_simulation *simulation)
{
	uint64_t	time;

	time = get_time_ms();
	pthread_mutex_lock(&simulation->mut);
	simulation->current_time = time;
	pthread_mutex_unlock(&simulation->mut);
}

uint64_t	get_current_time_(t_simulation *simulation)
{
	uint64_t	time;

	pthread_mutex_lock(&simulation->mut);
	time = simulation->current_time;
	pthread_mutex_unlock(&simulation->mut);
	return (time);
}
