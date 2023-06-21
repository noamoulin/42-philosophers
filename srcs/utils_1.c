/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noa <noa@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:19:00 by noa               #+#    #+#             */
/*   Updated: 2023/06/17 14:02:36 by noa              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include "../includes/utils.h"

size_t	m_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	m_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

bool	m_isspace(char chr)
{
	return (chr == ' ' || chr == '\f' || chr == '\n' || \
			chr == '\r' || chr == '\t' || chr == '\v');
}

bool	m_isdigit(char chr)
{
	return (chr >= '0' && chr <= '9');
}

bool	m_str_is_digit(const char *str)
{
	if (!m_isdigit(*str))
		return (false);
	while (*str)
	{
		if (!m_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}
