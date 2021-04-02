#ifndef PHILOSOPHERS_42_H
# define PHILOSOPHERS_42_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_data
{
	long	begin;
	int		id;
	int		round;
	long	time_to_die;
	long	time_to_sleep;
	long	time_to_eat;
	int		nb_time_to_eat;
}			t_data;

pthread_mutex_t forks;

long time_past;

#endif
