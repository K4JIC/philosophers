#include "philo.h"
#include <unistd.h>

int	philo_self_funeral(t_philo_thread_info *philo_info, int remaining_life_us)
{
	*philo_info->Im_died = 1;
	usleep(remaining_life_us);
	return (SUCCESS);
}

int	philo_write(t_philo_thread_info *philo_info, char *msg)
{
	unsigned long long	time_us;

	if (get_time_duration_us(&time_us, philo_info->start_time_us) == FAILURE)
		return (GET_TIME_ERROR);
	pthread_mutex_lock(philo_info->write_lock);
	printf("%04lld %d %s\n", time_us / 1000, philo_info->philo_num, msg);
	pthread_mutex_unlock(philo_info->write_lock);
	return (SUCCESS);
}

int	philo_eat(t_philo_thread_info *philo_info)
{
	unsigned long long	now_time_us;
	unsigned long long	remaining_life_us;

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
	usleep(philo_info->time_to_die_us);
	philo_info->eat_count++;
	pthread_mutex_unlock(philo_info->rfork_lock);
	pthread_mutex_unlock(philo_info->lfork_lock);
	return (SUCCESS);
}

int	philo_sleep(t_philo_thread_info *philo_info)
{
	unsigned long long	now_time_us;
	unsigned long long	remaining_life_us;

	if (philo_write(philo_info, "is sleeping") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (get_time_duration_us(&now_time_us, philo_info->start_time_us) == FAILURE)
		return (GET_TIME_ERROR);
	usleep(philo_info->time_to_sleep_us);
	return (SUCCESS);
}

int	philo_think(t_philo_thread_info *philo_info)
{
	unsigned long long	now_time_us;
	unsigned long long	remaining_life_us;

	if (philo_write(philo_info, "is thinking") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (get_time_duration_us(&now_time_us, philo_info->start_time_us) == FAILURE)
		return (GET_TIME_ERROR);
	usleep(philo_info->time_to_die_us);
	return (SUCCESS);
}
