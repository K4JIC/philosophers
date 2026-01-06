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
	if (!ft_isnum(ascii[i]))
		return (FAIL);
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
	if (validate_atoi(&(iinfo->philo_max), argv[1]) == FAIL)
		return (FAIL);
	if (validate_atoi(&(iinfo->time_to_die_ms), argv[2]) == FAIL)
		return (FAIL);
	if (validate_atoi(&(iinfo->time_to_eat_ms), argv[3]) == FAIL)
		return (FAIL);
	if (validate_atoi(&(iinfo->time_to_sleep_ms), argv[4]) == FAIL)
		return (FAIL);
	if (argc == 6)
	{
		if (validate_atoi(&(iinfo->philo_must_eat), argv[5]) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}
