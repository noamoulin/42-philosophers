/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_attr_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomoulin <nomoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:18:13 by noa               #+#    #+#             */
/*   Updated: 2023/06/21 15:20:11 by nomoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/utils.h"
#include "../includes/simulation.h"
#include "../includes/philo.h"

bool	init_philo(t_philo *philo, uint32_t id, t_monitor *monitor)
{
	philo->simulation = &monitor->simulation;
	philo->id = id;
	philo->left_fork = &monitor->forks[id];
	philo->right_fork = &monitor->forks[(id + 1) % \
		monitor->simulation.params.nb_philo];
	philo->meal_number = 0;
	philo->eat_permission = false;
	philo->state = STANDBY;
	if (pthread_mutex_init(&philo->mut, NULL))
		return (false);
	return (true);
}

void	destroy_philo(t_philo *philo)
{
	pthread_mutex_destroy(&philo->mut);
}

t_philo_state	get_philo_state(t_philo *philo)
{
	t_philo_state	state;

	pthread_mutex_lock(&philo->mut);
	state = philo->state;
	pthread_mutex_unlock(&philo->mut);
	return (state);
}

t_philo_state	set_philo_state(t_philo *philo, t_philo_state state)
{
	uint64_t	time_;

	time_ = get_current_time_(philo->simulation);
	pthread_mutex_lock(&philo->mut);
	philo->state = state;
	philo->last_event_time = time_;
	pthread_mutex_unlock(&philo->mut);
	return (state);
}

uint64_t	get_last_meal_time(t_philo	*philo)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->mut);
	time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->mut);
	return (time);
}
