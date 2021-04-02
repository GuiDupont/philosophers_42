#include "../includes/Philosophers_42.h"

long	tv_to_milli(struct timeval *tv)
{
	return (tv->tv_sec * 1000 + tv->tv_usec / 1000);
}

void *eat_sleep_think(void *datas)
{
	t_data *data;
	struct timeval tv;
	long current;
	long last_time_eat;

	data = (t_data*)datas;
	last_time_eat = data->begin;
	while (1)
	{
		if (data->round >= 0)
		{
			gettimeofday(&tv, NULL);
			if (tv_to_milli(&tv) - last_time_eat > 10)
			{
				time_past = tv_to_milli(&tv) - data->begin;
				printf("%ld %d died\n", time_past, data->id);
				return (NULL);
			}
			pthread_mutex_lock(&forks);
			
			time_past = tv_to_milli(&tv) - data->begin;
			printf("%ld %d has taken a fork\n", time_past, data->id); 
			printf("%ld %d is eating\n", time_past, data->id);
			usleep(data->time_to_eat);
			pthread_mutex_unlock(&forks);
			time_past = tv_to_milli(&tv) - data->begin;
			printf("%ld %d is sleeping\n", time_past, data->id);
			usleep(data->time_to_sleep);
			time_past = tv_to_milli(&tv) - data->begin;
			printf("%ld %d is thinking\n", time_past, data->id);
			data->round--;
		}
		else
			break;
	}
	return (NULL);
}


int main(int ac, char **av)
{
	struct timeval tv;
	long begin;
	t_data *data;
	pthread_t *philos;
	int i;
	int nb_philo;
	long	time_to_die;
	long	time_to_sleep;
	long	time_to_eat;
	int		nb_time_to_eat;

	if (ac != 5 && ac != 6)
		return (1);
	nb_philo = atoi(av[1]);
	time_to_die = atoi(av[2]);
	time_to_eat = atoi(av[3]);
	time_to_sleep = atoi(av[4]);
	if (ac == 6)
		nb_time_to_eat = atoi(av[5]);	
	data = malloc(sizeof(*data) * (nb_philo + 1));
	philos = malloc(sizeof(*philos) * (nb_philo + 1));
	i = 1;
	if (pthread_mutex_init(&forks, NULL) != 0)
    {
        printf("\n Mutex init failed\n");
        return 1;
    }
	while (i <= nb_philo)
	{
		gettimeofday(&tv, NULL);
		data[i].begin = tv_to_milli(&tv);
		data[i].id = i;
		data[i].round = nb_philo;
		data[i].time_to_die = time_to_die;
		data[i].time_to_sleep = time_to_sleep;
		data[i].time_to_eat = time_to_eat;
		pthread_create(&philos[i], NULL, eat_sleep_think, &data[i]);
		i++;
	}
	i = 0;
	while (i <= nb_philo)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&forks);
	// printf("programme started at %ld millisecondes\n", begin);
	// sleep(1);
	// gettimeofday(&tv, NULL);
	// printf("%ld millisecondes past\n", tv_to_milli(&tv) - begin);
	
}