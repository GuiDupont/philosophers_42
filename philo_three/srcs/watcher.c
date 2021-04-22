#include "../includes/Philosophers_42.h"

void	*watch_eaten(void *philos)
{
	t_philo *philo;
	
	philo = (t_philo*)philos;
	sem_wait(philo->stop);
	g_stop = 1;
	sem_post(philo->stop);
	sem_post(philo->eaten);
	//printf("philo %d out\n", philo->id);
	exit(0);
}


void	*watch_death(void *philo_void)
{
	t_philo		*philos;
	long long	diff;
    long long	now;

	philos = (t_philo*)philo_void;
	while (1)
	{
        now = get_time_in_milli();
		diff = now - philos->last_time_eat;
		if (diff >= philos->time_to_die && philos->nb_time_to_eat != -2)
		{
			print_log(now, philos->id + 1, "died\n", philos);
			sem_post(philos->stop);
			g_stop = philos[0].id;
			break ;
		}
	}
	return (NULL);
}

int		launch_watcher(t_philo *philos, pthread_t *watcher_dead, pthread_t *watcher_eaten)
{
	pthread_create(watcher_dead, NULL, watch_death, philos);
	pthread_create(watcher_eaten, NULL, watch_eaten, philos);
	return (1);
}
