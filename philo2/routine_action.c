#include "philo.h"
#include <unistd.h>

int	philo_self_funeral(t_thread_info *tinfo, int remaining_life_us)
{
	*tinfo->Im_died = 1;
	usleep(remaining_life_us);
	return (SUCCESS);
}

int	philo_write(t_thread_info *tinfo, char *msg)
{
	unsigned long long	time_us;

	if (get_time_duration_us(&time_us, tinfo->start_time_us) == FAILURE)
		return (GET_TIME_ERROR);
	pthread_mutex_lock(tinfo->write_lock);
	printf("%04lld %d %s\n", time_us / 1000, tinfo->philo_num, msg);
	pthread_mutex_unlock(tinfo->write_lock);
	return (SUCCESS);
}

int	philo_eat(t_thread_info *tinfo)
{
	unsigned long long	now_time_us;
	unsigned long long	remaining_life_us;

	pthread_mutex_lock(tinfo->rfork_lock);
	if (philo_write(tinfo, "has taken a fork") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	pthread_mutex_lock(tinfo->lfork_lock);
	if (get_time_us(&tinfo->last_eat_us) == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (philo_write(tinfo, "has taken a fork") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (philo_write(tinfo, "is eating") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (get_time_duration_us(&now_time_us, tinfo->start_time_us) == FAILURE)
		return (GET_TIME_ERROR);
	remaining_life_us = tinfo->time_to_sleep_us + now_time_us;
	if (remaining_life_us < tinfo->time_to_die_us)
	{
		philo_self_funeral(tinfo, remaining_life_us);
		return (FAILURE);
	}
	usleep(tinfo->time_to_die_us);
	tinfo->eat_count++;
	pthread_mutex_unlock(tinfo->rfork_lock);
	pthread_mutex_unlock(tinfo->lfork_lock);
	return (SUCCESS);
}

int	philo_sleep(t_thread_info *tinfo)
{
	unsigned long long	now_time_us;
	unsigned long long	remaining_life_us;

	if (philo_write(tinfo, "is sleeping") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (get_time_duration_us(&now_time_us, tinfo->start_time_us) == FAILURE)
		return (GET_TIME_ERROR);
	remaining_life_us = tinfo->time_to_sleep_us + now_time_us;
	if (remaining_life_us < tinfo->time_to_die_us)
	{
		philo_self_funeral(tinfo, remaining_life_us);
		return (FAILURE);
	}
	usleep(tinfo->time_to_sleep_us);
	return (SUCCESS);
}

int	philo_think(t_thread_info *tinfo)
{
	unsigned long long	now_time_us;
	unsigned long long	remaining_life_us;

	if (philo_write(tinfo, "is thinking") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (get_time_duration_us(&now_time_us, tinfo->start_time_us) == FAILURE)
		return (GET_TIME_ERROR);
	remaining_life_us = tinfo->time_to_sleep_us + now_time_us;
	if (remaining_life_us < tinfo->time_to_die_us)
	{
		philo_self_funeral(tinfo, remaining_life_us);
		return (FAILURE);
	}
	usleep(tinfo->time_to_die_us);
	return (SUCCESS);
}
