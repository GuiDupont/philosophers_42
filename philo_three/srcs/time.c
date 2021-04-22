#include "../includes/Philosophers_42.h"

long long	tv_to_milli(struct timeval *tv)
{
	return (tv->tv_sec * 1000 + tv->tv_usec / 1000);
}

long long	get_time_in_milli(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_sleep(long long time)
{
	long long start;

	start = get_time_in_milli();
	while (get_time_in_milli() - start < time)
		usleep(400);
}
