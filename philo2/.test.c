#include <sys/time.h>
#include <stdio.h>
int	main(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	printf("sec  = %ld\nusec = %ld\n", tv.tv_sec, tv.tv_usec);
	unsigned long long time = tv.tv_sec * 1000000 + tv.tv_usec;
	printf("usec = %lld", time);
}