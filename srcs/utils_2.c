/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noa <noa@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:19:07 by noa               #+#    #+#             */
/*   Updated: 2023/06/17 16:41:42 by noa              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include "../includes/utils.h"
#include "../includes/simulation.h"
#include "../includes/philo.h"
#include <stdio.h>

int32_t	atoi32(const char *str)
{
	int		i;
	int32_t	nb;
	int		sign;

	if (!str)
		return (0);
	i = 0;
	nb = 0;
	sign = 1;
	while (m_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (m_isdigit(str[i]))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}

uint64_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	say_state(t_philo *philo, char *str)
{
	uint64_t	time;
	uint32_t	id;

	time = philo->last_event_time - philo->simulation->start_time;
	id = philo->id;
	pthread_mutex_lock(&philo->simulation->speaker);
	printf("%lu %u %s\n", time, ++id, str);
	pthread_mutex_unlock(&philo->simulation->speaker);
}
