#include "philo.h"
#include <unistd.h>

int	philo_usleep(t_thread_info *tinfo, time_t wait_time_us)
{
	unsigned long long	unit_quotient;
	unsigned long long	unit_remainder;
	unsigned long long	i;
	int					isfinished;

	unit_quotient = wait_time_us / tinfo->unit_time_us;
	unit_remainder = wait_time_us % tinfo->unit_time_us;
	i = 0;
	while (i < unit_quotient)
	{
		isfinished = is_finished(tinfo);
		if (isfinished == GET_TIME_ERROR)
			return (GET_TIME_ERROR);
		if (isfinished)
			return (FAILURE);
		usleep(tinfo->unit_time_us);
		i++;
	}
	usleep(unit_remainder);
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
	int	wait_ret;

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
	wait_ret = philo_usleep(tinfo, tinfo->time_to_eat_ms * 1000);
	if (wait_ret == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (wait_ret == FAILURE)
	{
		philo_write(tinfo, "waitret_fail");
		return (FAILURE);
	}
	tinfo->eat_count++;
	pthread_mutex_unlock(tinfo->rfork_lock);
	pthread_mutex_unlock(tinfo->lfork_lock);
	return (SUCCESS);
}

int	philo_sleep(t_thread_info *tinfo)
{
	int	wait_ret;

	if (philo_write(tinfo, "is sleeping") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	wait_ret = philo_usleep(tinfo, tinfo->time_to_sleep_ms * 1000);
	if (wait_ret == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (wait_ret == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	philo_think(t_thread_info *tinfo)
{
	int	wait_ret;

	if (philo_write(tinfo, "is thinking") == FAILURE)
		return (FAILURE);
	wait_ret = philo_usleep(tinfo, tinfo->time_to_think_ms * 1000);
	if (wait_ret == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (wait_ret == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
