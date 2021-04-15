#include "../includes/Philosophers_42.h"

void	*watch_death(void *philo_void)
{
	int i;
	t_philo *philos;
	long long diff;
    long long now;

	i = 0;
	philos = (t_philo*)philo_void;
	while (i < philos->nb_philo)
	{
        now = get_time_in_milli();
		diff = now - philos[i].last_time_eat;
		if (diff >= philos->time_to_die && philos[i].nb_time_to_eat != -2)
		{
            print_log(now, philos->id + 1, "die\n", philos);
			g_stop = philos[0].id;
			pthread_mutex_lock(philos->print);
			break ;
		}
		i++;
		if (i == philos->nb_philo)
			i = 0;
	}
	return (NULL);
}

// void	launch_watcher(t_philo *philos, pthread_t *watcher)
// {
// 	pthread_create(watcher, NULL, watch_death, philos);
// }
