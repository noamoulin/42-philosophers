/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noa <noa@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:18:55 by noa               #+#    #+#             */
/*   Updated: 2023/06/21 22:02:43 by noa              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/simulation.h"
#include "../includes/philo.h"
#include "error.h"

void	*philo_thread(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo_routine(philo, philo->simulation);
	return (EXIT_SUCCESS);
}

void	philo_routine(t_philo *philo, t_simulation *simulation)
{
	t_philo_state	state;

	while (get_simulation_state(simulation) != STOP)
	{
		state = get_philo_state(philo);
		if (state == STANDBY)
			check_standby(philo, simulation);
		if (state == EATING)
			check_eat(philo, simulation);
		if (state == SLEEPING)
			check_sleep(philo, simulation);
		if (state == THINKING)
			check_thinking(philo, simulation);
	}
	terminate_philo(philo);
}
