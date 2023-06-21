/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_attr_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomoulin <nomoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:18:20 by noa               #+#    #+#             */
/*   Updated: 2023/06/21 15:21:41 by nomoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/utils.h"
#include "../includes/simulation.h"
#include "../includes/philo.h"

t_philo_snapshot	get_philo_snapshot(t_philo *philo)
{
	t_philo_snapshot	snap;

	pthread_mutex_lock(&philo->mut);
	snap.last_meal_time = philo->last_meal_time;
	snap.meal_number = philo->meal_number;
	snap.state = philo->state;
	snap.eat_permission = philo->eat_permission;
	pthread_mutex_unlock(&philo->mut);
	return (snap);
}

void	allow_eat(t_philo *philo)
{
	pthread_mutex_lock((&philo->mut));
	philo->eat_permission = true;
	pthread_mutex_unlock(&philo->mut);
}

bool	can_eat(t_philo *philo)
{
	bool	allow_eat;

	pthread_mutex_lock((&philo->mut));
	allow_eat = philo->eat_permission;
	pthread_mutex_unlock(&philo->mut);
	return (allow_eat);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock((philo->right_fork));
	say_state(philo, "has taken a fork");
	pthread_mutex_lock((philo->left_fork));
	say_state(philo, "has taken a fork");
}

void	relase_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->mut);
	philo->eat_permission = false;
	pthread_mutex_unlock(&philo->mut);
}
