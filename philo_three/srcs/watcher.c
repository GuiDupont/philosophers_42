#include "../includes/Philosophers_42.h"

void	*watch_eaten(void *philos)
{
	t_philo *philo;
	
	philo = (t_philo*)philos;
	sem_wait(philo->stop);
	if (g_stop == -1)
		g_stop = -2;
	return (NULL);
}


void	*watch_death(void *philo_void)
{
	t_philo		*philos;
	long long	diff;
    long long	now;
	int			i;

	philos = (t_philo*)philo_void;
	i = -1;
	while (1)
	{
        now = get_time_in_milli();
		diff = now - philos->last_time_eat;
		if (diff >= philos->time_to_die && philos->nb_time_to_eat != -2)
		{
			sem_wait(philos->print);
			if (g_stop == -1)
			{
				printf("%lld %d died\n", now - g_beginning, philos->id + 1);
				g_stop = philos[0].id;
			}
			while (++i < philos->nb_philo)
				sem_post(philos->stop);
			sem_post(philos->print);
			break ;
		}
		if (g_stop != -1)
			break ;
	}
	return (NULL);
}

int		launch_watcher(t_philo *philos, pthread_t *watcher_dead, pthread_t *watcher_eaten)
{
	pthread_create(watcher_dead, NULL, watch_death, philos);
	pthread_create(watcher_eaten, NULL, watch_eaten, philos);
	return (1);
}
