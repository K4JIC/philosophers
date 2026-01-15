/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:27:14 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/06 18:42:29 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>
/**
 * receive "char **argv"
 * pack "char **argv" in "t_input_info input_info"
 * return input_info
 */
static int	ft_isnum(char c)
{
	return ('0' <= c && c <= '9');
}

static int	ft_isspace(char c)
{
	return (c == ' ' || (9 <= c && c <= 13));
}

#include <stdio.h>

static int	ft_strcmp(char *str1, char *str2)
{
	unsigned char	*uc_str1;
	unsigned char	*uc_str2;
	int				i;

	uc_str1 = (unsigned char *)str1;
	uc_str2 = (unsigned char *)str2;
	i = 0;
	while (uc_str1[i] && uc_str2[i] && uc_str1[i] == uc_str2[i])
		i++;
	return (uc_str1[i] - uc_str2[i]);
}

static int	is_integer(char *ascii)
{
	size_t	len;

	if (!ascii)
		return (0);
	len = 0;
	while (ascii[len])
		len++;
	if (ascii[0] == '-')
	{
		if (len < 11)
			return (1);
		if (len > 11)
			return (0);
		if (len == 11 && ft_strcmp(ascii, INT_MIN_CHAR) > 0)
			return (0);
	}
	else
	{
		if (len < 10)
			return (1);
		if (len > 10)
			return (0);
		if (len == 10 && ft_strcmp(ascii, INT_MAX_CHAR) > 0)
			return (0);
	}
	return (1);
}

static int	validate_atoi(int *integer, char *ascii)
{
	int	res;
	int	i;
	int	sign;

	res = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(ascii[i]))
		i++;
	if (ascii[i] == '-' || ascii[i] == '+')
	{
		if (ascii[i] == '-')
			sign = -1;
		i++;
	}
	if (!is_integer(ascii) || !ft_isnum(ascii[i]))
		return (FAILURE);
	while (ft_isnum(ascii[i]))
	{
		res = res * 10 + (ascii[i] - '0');
		i++;
	}
	*integer = res * sign;
	return (SUCCESS);
}

int	set_argv(int argc, char **argv, t_input_info *iinfo)
{
	if (validate_atoi(&(iinfo->philo_max), argv[1]) == FAILURE)
		return (FAILURE);
	if (validate_atoi(&(iinfo->time_to_die_ms), argv[2]) == FAILURE)
		return (FAILURE);
	if (validate_atoi(&(iinfo->time_to_eat_ms), argv[3]) == FAILURE)
		return (FAILURE);
	if (validate_atoi(&(iinfo->time_to_sleep_ms), argv[4]) == FAILURE)
		return (FAILURE);
	if (argc == 6)
	{
		if (validate_atoi(&(iinfo->philo_must_eat), argv[5]) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
