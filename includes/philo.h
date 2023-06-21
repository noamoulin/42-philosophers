/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noa <noa@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:19:27 by noa               #+#    #+#             */
/*   Updated: 2023/06/17 15:24:51 by noa              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdint.h>
# include <stdbool.h>
# include <pthread.h>

typedef struct s_simulation	t_simulation;
typedef struct s_monitor	t_monitor;

typedef enum e_philo_state
{
	STANDBY,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
}	t_philo_state;

typedef struct s_philo_snapshot
{
	t_philo_state		state;
	uint64_t			last_meal_time;
	int32_t				meal_number;
	bool				eat_permission;
}	t_philo_snapshot;

typedef struct s_philo
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	mut;
	t_philo_state	state;
	t_simulation	*simulation;
	uint64_t		last_meal_time;
	uint64_t		last_event_time;
	uint32_t		id;
	int32_t			meal_number;
	bool			eat_permission;
}	t_philo;

t_philo_snapshot	get_philo_snapshot(t_philo *philo);
t_philo_state		get_philo_state(t_philo *philo);
t_philo_state		set_philo_state(t_philo *philo, t_philo_state state);
uint64_t			get_last_meal_time(t_philo *philo);
bool				init_philo(t_philo *philo, uint32_t id, t_monitor *env);
void				destroy_philo(t_philo *philo);
void				allow_eat(t_philo *philo);
bool				can_eat(t_philo *philo);
void				take_forks(t_philo *philo);
void				relase_forks(t_philo *philo);
void				new_meal(t_philo *philo, uint64_t time);
void				terminate_philo(t_philo *philo);
void				*philo_thread(void	*data);
void				philo_routine(t_philo *philo, t_simulation *simulation);
void				check_standby(t_philo *philo, t_simulation *simulation);
void				check_eat(t_philo *philo, t_simulation *simulation);
void				check_sleep(t_philo *philo, t_simulation *simulation);
void				check_thinking(t_philo *philo, t_simulation *simulation);
void				say_state(t_philo *philo, char *str);

#endif