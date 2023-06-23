/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noa <noa@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:18:39 by noa               #+#    #+#             */
/*   Updated: 2023/06/23 13:23:45 by noa              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"
#include "../includes/simulation.h"
#include "../includes/philo.h"

void	check_standby(t_philo *philo, t_simulation *simulation)
{
	if (get_simulation_state(simulation) == START)
	{
		set_philo_state(philo, THINKING);
		say_state(philo, "is thinking");
	}
}

void	check_eat(t_philo *philo, t_simulation *simulation)
{
	int32_t	time_since_meal;

	time_since_meal = (int32_t)get_current_time_(simulation) - \
		get_last_meal_time(philo);
	if (time_since_meal > simulation->params.time_to_die)
	{
		relase_forks(philo);
		set_philo_state(philo, DEAD);
		say_state(philo, "died");
	}
	else if (time_since_meal >= simulation->params.time_to_eat)
	{
		set_philo_state(philo, SLEEPING);
		relase_forks(philo);
		say_state(philo, "is sleeping");
		usleep(300);
	}
}

void	check_sleep(t_philo *philo, t_simulation *simulation)
{
	int32_t	time_since_meal;

	time_since_meal = (int32_t)(get_current_time_(simulation) - \
		get_last_meal_time(philo));
	if (time_since_meal > simulation->params.time_to_die)
	{
		set_philo_state(philo, DEAD);
		say_state(philo, "died");
	}
	else if (time_since_meal >= (simulation->params.time_to_eat + \
		simulation->params.time_to_sleep))
	{
		set_philo_state(philo, THINKING);
		say_state(philo, "is thinking");
		usleep(10);
	}
}

void	check_thinking(t_philo *philo, t_simulation *simulation)
{
	int32_t	time_since_meal;

	time_since_meal = (int32_t)(get_current_time_(simulation) - \
		get_last_meal_time(philo));
	if (time_since_meal > simulation->params.time_to_die)
	{
		set_philo_state(philo, DEAD);
		say_state(philo, "died");
	}
	else if (can_eat(philo))
	{
		set_philo_state(philo, EATING);
		take_forks(philo);
		new_meal(philo, philo->last_event_time);
		say_state(philo, "is eating");
		usleep(300);
	}
}
