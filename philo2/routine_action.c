#include "philo.h"
#include <pthread.h>
#include <unistd.h>

int	philo_busy_wait_usleep(t_philo_thread_info *philo_info, useconds_t wait_time_us)
{
	t_time_us	start_clock_us;
	t_time_us	now_us;
	size_t		i;

	if (get_time_us(&start_clock_us) == FAILURE)
		return (GET_TIME_ERROR);
	i = 0;
	while (1)
	{
		if (get_time_us(&now_us) == FAILURE)
			return (GET_TIME_ERROR);
		if (now_us - start_clock_us > wait_time_us)
			break ;
		if (is_finished(philo_info))
			return (FAILURE);
		usleep(UNIT_TIME_US);
		i++;
	}
	return (SUCCESS);
}

int	philo_write(t_philo_thread_info *philo_info, char *msg)
{
	t_time_us	time_us;

	if (get_time_duration_us(&time_us, philo_info->start_clock_us) == FAILURE)
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
	if (get_time_us(philo_info->last_eat_clock_us) == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (philo_write(philo_info, "has taken a fork") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (philo_write(philo_info, "is eating") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (get_time_duration_us(&now_time_us, philo_info->start_clock_us) == FAILURE)
		return (GET_TIME_ERROR);
	if (philo_busy_wait_usleep(philo_info, philo_info->time_to_eat_us) == FAILURE)
	{
		pthread_mutex_unlock(philo_info->rfork_lock);
		pthread_mutex_unlock(philo_info->lfork_lock);
		return (FAILURE);
	}
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
	if (get_time_duration_us(&now_time_us, philo_info->start_clock_us) == FAILURE)
		return (GET_TIME_ERROR);
	if (philo_busy_wait_usleep(philo_info, philo_info->time_to_sleep_us) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	philo_think(t_philo_thread_info *philo_info)
{
	t_time_us	now_time_us;
	t_time_us	remaining_life_us;

	if (philo_write(philo_info, "is thinking") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (get_time_duration_us(&now_time_us, philo_info->start_clock_us) == FAILURE)
		return (GET_TIME_ERROR);
	if (philo_busy_wait_usleep(philo_info, philo_info->time_to_think_us) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
