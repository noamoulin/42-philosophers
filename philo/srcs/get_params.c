/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noa <noa@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:17:34 by noa               #+#    #+#             */
/*   Updated: 2023/06/21 22:08:48 by noa              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../includes/utils.h"
#include "../includes/simulation.h"

#define ARG_MAX "1000000000"

static bool	valid_arg(char *arg)
{
	if (!m_str_is_digit(arg))
		return (false);
	if (arg[0] == '0')
		return (false);
	if (m_strlen(arg) > m_strlen(ARG_MAX))
		return (false);
	if (m_strlen(arg) == (m_strlen(ARG_MAX)) && m_strcmp(arg, ARG_MAX) > 0)
		return (false);
	return (true);
}

bool	set_params(t_params	*params, int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (false);
	i = 0;
	while (++i < ac)
	{
		if (!valid_arg(av[i]))
			return (false);
	}
	params->nb_philo = atoi32(av[1]);
	params->time_to_die = atoi32(av[2]);
	params->time_to_eat = atoi32(av[3]);
	params->time_to_sleep = atoi32(av[4]);
	params->time_to_sleep_us = params->time_to_sleep;
	params->time_to_eat_us = params->time_to_eat;
	if (ac > 5)
		params->meal_number = atoi32(av[5]);
	else
		params->meal_number = -1;
	return (true);
}
