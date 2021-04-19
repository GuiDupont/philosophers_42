#include "../includes/Philosophers_42.h"

void	*watch_death(void *philo_void)
{
	t_philo *philos;
	long long diff;
    long long now;

	philos = (t_philo*)philo_void;
	while (1)
	{
        now = get_time_in_milli();
		diff = now - philos->last_time_eat;
		if (diff >= philos->time_to_die && philos->nb_time_to_eat != -2)
		{
			print_log(now, philos->id + 1, "died\n", philos);
			sem_wait(philos->print);
			g_stop = philos[0].id;
			break ;
		}
	}
	return (NULL);
}

int		launch_watcher(t_philo *philos, pthread_t *watcher)
{
	pthread_create(watcher, NULL, watch_death, philos);
	return (1);
}
