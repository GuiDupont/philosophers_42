#ifndef PHILOSOPHERS_42_H
# define PHILOSOPHERS_42_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int		g_stop;
long long g_beginning;

typedef struct	s_data
{

	
	
}				t_data;


typedef struct	s_philo
{
	int				id;
	int				nb_philo;
	int				min_fork;
	int				max_fork;
	int				nb_time_to_eat;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	long long		beginning;
	long long		last_time_eat;
	pthread_mutex_t *forks;

}				t_philo;

long long	tv_to_milli(struct timeval *tv);

long long	get_time_in_milli(void);
int			get_min_fork(t_philo *philo);
int			get_max_fork(t_philo *philo);
void   		print_log(unsigned long timestamp, int id, char *log);
char		*ft_strcpy(char *dest, char *src);
int			ft_strlen(const char *str);

int			get_min(int a, int b);

int			get_max(int a, int b);

t_philo	*set_up_philos(char **av);
int		set_up_common_data(int ac, char **av, t_data *common_data);
pthread_mutex_t *set_up_mutex(int nb_fork);



#endif
