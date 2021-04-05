#ifndef PHILOSOPHERS_42_H
# define PHILOSOPHERS_42_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct	s_data
{
	int				nb_philo;
	int				stop;
	int				nb_time_to_eat;
	long			beginning;
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	pthread_mutex_t *forks;
}				t_data;


typedef struct	s_philo
{
	int				id;
	long			last_time_eat;
	t_data			*common_data;
}				t_philo;

long	tv_to_milli(struct timeval *tv);

long	get_time_in_milli(void);

int		get_min(int a, int b);

int		get_max(int a, int b);


#endif
