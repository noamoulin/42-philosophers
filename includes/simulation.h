/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noa <noa@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:19:33 by noa               #+#    #+#             */
/*   Updated: 2023/06/21 22:02:12 by noa              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include <stdint.h>
# include <pthread.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_philo			t_philo;
typedef struct s_philo_snapshot	t_philo_snapshot;

typedef enum e_simulation_state
{
	WAIT,
	START,
	STOP
}	t_simulation_state;

typedef struct s_params
{
	uint64_t	time_to_sleep_us;
	uint64_t	time_to_eat_us;
	int32_t		nb_philo;
	int32_t		time_to_die;
	int32_t		time_to_eat;
	int32_t		time_to_sleep;
	int32_t		meal_number;
}	t_params;

typedef struct s_simulation
{
	t_simulation_state	state;
	pthread_mutex_t		speaker;
	pthread_mutex_t		mut;
	t_params			params;
	uint64_t			start_time;
	uint64_t			current_time;
}	t_simulation;

typedef struct s_monitor
{
	t_philo_snapshot	*snapshots;
	pthread_mutex_t		*forks;
	t_simulation		simulation;
	pthread_t			*threads;
	t_philo				*philos;
}	t_monitor;

t_simulation_state	get_simulation_state(t_simulation *simulation);
bool				alloc_monitor(t_monitor *monitor);
bool				init_monitor_mutex(t_monitor *monitor);
bool				init_simulation(t_simulation *simulation, t_params params);
bool				init_monitor_philos(t_monitor *monitor);
void				free_monitor(t_monitor *monitor);
void				destroy_monitor_mutex(t_monitor *monitor);
void				destroy_simulation(t_simulation *simulation);
bool				start_monitor(t_monitor	*monitor);
void				stop_monitor(t_monitor *monitor);
bool				one_dead(t_monitor *monitor);
bool				all_eat_enought(t_monitor *monitor);
void				maj_snaps(t_monitor *monitor);
bool				init_monitor(t_monitor *monitor, t_params params);
void				destroy_monitor(t_monitor *monitor);
void				set_simulation_state(t_simulation *simulation, \
	t_simulation_state state);
void				give_eat_permission(t_monitor *monitor);
bool				set_params(t_params *params, int ac, char **av);
void				take_current_time(t_simulation *simulation);
uint64_t			get_current_time_(t_simulation *simulation);

#endif