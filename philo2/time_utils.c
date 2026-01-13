
#include "philo.h"
#include <unistd.h>

static unsigned long long	convert_tv_to_ull(struct timeval tv)
{
	unsigned long long	time_us;

	time_us = tv.tv_sec * SEC_TO_USEC + tv.tv_usec;
	return (time_us);
}

int	get_time_us(unsigned long long *time_us)
{
	struct timeval		tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (FAILURE);
	*time_us = convert_tv_to_ull(tv);
	return (SUCCESS);
}

int	get_time_duration_us(unsigned long long *time_us,
						unsigned long long start_time_us)
{
	unsigned long long	now_time_us;

	if (get_time_us(&now_time_us) == FAILURE)
		return (FAILURE);
	*time_us = now_time_us - start_time_us;
	return (SUCCESS);
}
