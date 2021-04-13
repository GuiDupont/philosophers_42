#include "../includes/Philosophers_42.h"

void	kill_philos(int *philo_pid, int nb_philos)
{
	int i;

	i = 0;
	(void)philo_pid;
	while (i < nb_philos)
	{
		kill(philo_pid[i], 9);
		i++;
	}
	free(philo_pid);
}

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
		if (diff >= philos->time_to_die && philos[i].nb_time_to_eat != -2)
		{
            print_log(now, philos->id + 1, "die\n", philo);
			printf("last time eat = %lld\n", philos[i])
			sem_wait(philos->print);
			kill_philos(philos->philo_pid, philos->nb_philo);
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
