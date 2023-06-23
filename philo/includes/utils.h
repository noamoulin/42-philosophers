/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noa <noa@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:19:38 by noa               #+#    #+#             */
/*   Updated: 2023/06/17 13:45:15 by noa              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include "philo.h"

uint64_t	get_time_ms(void);
int32_t		atoi32(const char *str);
size_t		m_strlen(const char *str);
bool		m_isspace(char chr);
bool		m_isdigit(char chr);
bool		m_str_is_digit(const char *str);
void		say_state(t_philo *philo, char *str);
int			m_strcmp(const char *s1, const char *s2);

#endif