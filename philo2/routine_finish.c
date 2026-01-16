#include "philo.h"
#include <stdio.h>

static int	process_is_finished(t_philo_thread_info *philo_info)
{
	int	ret;

	pthread_mutex_lock(philo_info->flag_lock);
	ret = *philo_info->finish_flag;
	pthread_mutex_unlock(philo_info->flag_lock);
	if (ret == 1)
		return (1);
	return (0);
}

static int	is_alive(t_philo_thread_info *philo_info)
{
	unsigned long long	hungry_time_us;

	if (get_time_duration_us(&hungry_time_us, *philo_info->last_eat_us))
		return (GET_TIME_ERROR);
	if (hungry_time_us / 1000 > (unsigned long long)philo_info->time_to_die_us)
	{
		// printf("%d ", philo_info->philo_num);
		// printf("hungry = %lld\n", hungry_time_us);
		// printf("%d ", philo_info->philo_num);
		// printf("last_eat = %lld\n", philo_info->last_eat_us);
		// philo_write(philo_info, "is_alive() fail");
		*philo_info->Im_died = 1;
		return (0);
	}
	return (1);
}

static int	is_full(t_philo_thread_info *philo_info)
{
	if (!philo_info->must_eat_option)
		return (0);
	if (philo_info->eat_count >= philo_info->must_eat)
	{
		// philo_write(philo_info, "is_full() fail");
		return (1);
	}
	return (0);
}

static int	thread_is_finished(t_philo_thread_info *philo_info)
{
	int	isalive;

	isalive = is_alive(philo_info);
	if (isalive == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (is_full(philo_info) || !isalive)
	{
		// philo_write(philo_info, "thread_is_finished() fail");
		pthread_mutex_lock(philo_info->flag_lock);
		*philo_info->finish_flag = 1;
		pthread_mutex_unlock(philo_info->flag_lock);
		return (1);
	}
	return (0);
}

int	is_finished(t_philo_thread_info *philo_info)
{
	int	thisfinished;

	thisfinished = thread_is_finished(philo_info);
	if (thisfinished == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (thisfinished)
	{
		// philo_write(philo_info, "is_finished() fail");
		return (FAILURE);
	}
	if (process_is_finished(philo_info))
		return (FAILURE);
	return (SUCCESS);
}
