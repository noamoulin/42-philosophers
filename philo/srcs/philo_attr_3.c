/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_attr_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noa <noa@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:18:24 by noa               #+#    #+#             */
/*   Updated: 2023/06/17 14:06:05 by noa              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/utils.h"
#include "../includes/simulation.h"
#include "../includes/philo.h"

void	new_meal(t_philo *philo, uint64_t time)
{
	pthread_mutex_lock(&philo->mut);
	philo->last_meal_time = time;
	++philo->meal_number;
	pthread_mutex_unlock(&philo->mut);
}

void	terminate_philo(t_philo *philo)
{
	if (get_philo_state(philo) == EATING)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	destroy_philo(philo);
	pthread_exit(EXIT_SUCCESS);
}
