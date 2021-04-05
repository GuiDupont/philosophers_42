#include "../includes/Philosophers_42.h"

long	tv_to_milli(struct timeval *tv)
{
	return (tv->tv_sec * 1000 + tv->tv_usec / 1000);
}

long	get_time_in_milli(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int		get_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int		get_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
