#include "philo.h"

int	philo_busy_wait_usleep(t_philo_thread_info *philo_info, t_time_us time_us)
{
	size_t	quotient_time_us;
	size_t	remainder_time_us;
	size_t	i;

	quotient_time_us = time_us / UNIT_TIME_US;
	remainder_time_us = time_us % UNIT_TIME_US;
	i = 0;
	while (i < quotient_time_us)
	{
		if (is_finished(philo_info))
			return (FAILURE);
		usleep(UNIT_TIME_US);
		i++;
	}
	if (is_finished(philo_info))
		return (FAILURE);
	usleep(remainder_time_us);
	return (SUCCESS);
}

int	philo_write(t_philo_thread_info *philo_info, char *msg)
{
	t_time_us	time_us;

	if (get_time_duration_us(&time_us, philo_info->start_time_us) == FAILURE)
		return (GET_TIME_ERROR);
	pthread_mutex_lock(philo_info->write_lock);
	printf("%04lld %d %s\n", time_us / 1000, philo_info->philo_num, msg);
	pthread_mutex_unlock(philo_info->write_lock);
	return (SUCCESS);
}

int	philo_eat(t_philo_thread_info *philo_info)
{
	t_time_us	now_time_us;
	t_time_us	remaining_life_us;

	pthread_mutex_lock(philo_info->rfork_lock);
	if (philo_write(philo_info, "has taken a fork") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	pthread_mutex_lock(philo_info->lfork_lock);
	if (get_time_us(philo_info->last_eat_us) == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (philo_write(philo_info, "has taken a fork") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (philo_write(philo_info, "is eating") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (get_time_duration_us(&now_time_us, philo_info->start_time_us) == FAILURE)
		return (GET_TIME_ERROR);
	philo_busy_wait_usleep(philo_info, philo_info->time_to_die_us);
	philo_info->eat_count++;
	pthread_mutex_unlock(philo_info->rfork_lock);
	pthread_mutex_unlock(philo_info->lfork_lock);
	return (SUCCESS);
}

int	philo_sleep(t_philo_thread_info *philo_info)
{
	t_time_us	now_time_us;
	t_time_us	remaining_life_us;

	if (philo_write(philo_info, "is sleeping") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (get_time_duration_us(&now_time_us, philo_info->start_time_us) == FAILURE)
		return (GET_TIME_ERROR);
	philo_busy_wait_usleep(philo_info, philo_info->time_to_sleep_us);
	return (SUCCESS);
}

int	philo_think(t_philo_thread_info *philo_info)
{
	t_time_us	now_time_us;
	t_time_us	remaining_life_us;

	if (philo_write(philo_info, "is thinking") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (get_time_duration_us(&now_time_us, philo_info->start_time_us) == FAILURE)
		return (GET_TIME_ERROR);
	philo_busy_wait_usleep(philo_info, philo_info->time_to_die_us);
	return (SUCCESS);
}
