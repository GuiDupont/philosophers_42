#include "../includes/Philosophers_42.h"

void	*watch_death(void *philo)
{
	int i;
	t_philo *philos;
	long long diff;
    long long now;

	i = 0;
	philos = (t_philo*)philo;
	while (i < philos->nb_philo)
	{
        now = get_time_in_milli();
		diff = now - philos[i].last_time_eat;
        //diff = get_time_in_milli() - philos[i].last_time_eat;
		if (diff >= philos->time_to_die)
		{
           // printf("diff = %lld last time eat: %lld et now = %lld \n", diff, philos[i].last_time_eat, now );
            print_log(get_time_in_milli(), philos->id + 1, "die\n");
			g_stop = philos[0].id;
			break ;
		}
		i++;
		if (i == philos->nb_philo)
			i = 0;
	}

	return (NULL);
}

int	launch_watcher(t_philo *philos)
{
	pthread_t watcher;

	pthread_create(&watcher, NULL, watch_death, philos);
	return (1);
}
