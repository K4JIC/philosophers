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
		if (len > 11
			|| (len == 11 && ft_strcmp(ascii, INT_MIN_CHAR) > 0))
			return (0);
	}
	else
	{
		if (len < 10)
			return (1);
		if (len > 10
			|| (len == 10 && ft_strcmp(ascii, INT_MAX_CHAR) > 0))
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
	while (ascii[i] == ' ' || (9 <= ascii[i] && ascii[i] <= 13))
		i++;
	if (ascii[i] == '-' || ascii[i] == '+')
	{
		if (ascii[i] == '-')
			sign = -1;
		i++;
	}
	if (!is_integer(ascii) || !('0' <= ascii[i] && ascii[i] <= '9'))
		return (FAILURE);
	while ('0' <= ascii[i] && ascii[i] <= '9')
	{
		res = res * 10 + (ascii[i] - '0');
		i++;
	}
	*integer = res * sign;
	return (SUCCESS);
}

int	set_argv(int argc, char **argv, t_input_info *input_info)
{
	int	time_to_die_int;
	int	time_to_eat_int;
	int	time_to_sleep_int;

	if (validate_atoi(&(input_info->philo_max), argv[1]) == FAILURE)
		return (FAILURE);
	if (validate_atoi(&(time_to_die_int), argv[2]) == FAILURE)
		return (FAILURE);
	if (validate_atoi(&(time_to_eat_int), argv[3]) == FAILURE)
		return (FAILURE);
	if (validate_atoi(&(time_to_sleep_int), argv[4]) == FAILURE)
		return (FAILURE);
	if (argc == 6)
	{
		if (validate_atoi(&(input_info->philo_must_eat), argv[5]) == FAILURE)
			return (FAILURE);
	}
	input_info->time_to_die_us = (t_time_us)time_to_die_int * 1000;
	input_info->time_to_eat_us = (t_time_us)time_to_eat_int * 1000;
	input_info->time_to_sleep_us = (t_time_us)time_to_sleep_int * 1000;
	return (SUCCESS);
}
