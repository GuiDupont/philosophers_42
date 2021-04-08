#include "../includes/Philosophers_42.h"

void	eat(t_philo *philo)
{
	usleep(100);
	pthread_mutex_lock(&philo->forks[philo->min_fork]);
	print_log(get_time_in_milli() - g_beginning, philo->id + 1, "has taken a fork\n");
	pthread_mutex_lock(&philo->forks[philo->max_fork]);
	print_log(get_time_in_milli() - g_beginning, philo->id + 1, "has taken a fork\n");	
	philo->last_time_eat = get_time_in_milli();
	print_log(get_time_in_milli() - g_beginning, philo->id + 1, "is eating\n");
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->forks[philo->min_fork]);
	pthread_mutex_unlock(&philo->forks[philo->max_fork]);
}

void 	*eat_sleep_think(void *philo_void)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo*)philo_void;
	i = 0;
	philo->last_time_eat = g_beginning;
	while (i != philo->nb_time_to_eat && g_stop == -1)
	{
		eat(philo);
		print_log(get_time_in_milli() - g_beginning, philo->id + 1, "is sleeping\n");
		usleep(philo->time_to_sleep);
		print_log(get_time_in_milli() - g_beginning, philo->id + 1, "is thinking\n");
		i++;
	}
	return (NULL);
}




// void	*watch_death(void *philos)
// {
// 	t_philo	*philo;
// 	long long diff;
// 	long time_to_die;

// 	philo = (t_philo*)philos;
// 	time_to_die = philo[0].common_data->time_to_die;
// 	while (g_stop == -1)
// 	{
// 		diff = get_time_in_milli() - philo[0].last_time_eat;
// 		if (diff >= time_to_die)
// 		{
// 			g_stop = philo[0].id;
// 			printf("%lld %d hasn't eat for %lld milliseconds, he died %lld millisecondes ago\n", get_time_in_milli() - philo->common_data->beginning, philo->id + 1, diff, diff - philo->common_data->time_to_die);
// 			break ;
// 		}
// 		usleep(9000);
// 	}
// 	return (NULL);
// }

void	*watch_death(void *philo)
{
	int i;
	t_philo *philos;
	long long diff;

	i = 0;
	philos = (t_philo*)philo;
	while (i < philos->nb_philo)
	{
		diff = get_time_in_milli() - philos[i].last_time_eat;
		if (diff >= philos->time_to_die)
		{
			g_stop = philos[0].id;
			printf("%lld %d hasn't eat for %lld milliseconds, he died %lld millisecondes ago\n", get_time_in_milli() - g_beginning, philos[i].id + 1, diff, diff - philos->time_to_die);
			break ;
		}
		i++;
		if (i == philos->nb_philo)
			i = 0;
		sleep(200);
	}
	return (NULL);
}

int	launch_watcher(t_philo *philos)
{
	pthread_t watcher;

	pthread_create(&watcher, NULL, watch_death, philos);
	return (1);
}

void	run_simulation(t_philo *philos)
{
	int i;
	pthread_t *philos_pthread;
	int	nb_philo;

	nb_philo = philos[0].nb_philo;
	philos_pthread = malloc(sizeof(*philos_pthread) * (nb_philo + 1));
	g_beginning = get_time_in_milli();
	i = 0;
	while (i < nb_philo)
	{
		pthread_create(&philos_pthread[i], NULL, eat_sleep_think, &philos[i]);
		i += 2;
	}
	i = 1;
	while (i < nb_philo)
	{
		pthread_create(&philos_pthread[i], NULL, eat_sleep_think, &philos[i]);
		i += 2;
	}

	launch_watcher(philos);
	i = 0;
	while (i < nb_philo)
	{
		pthread_join(philos_pthread[i], NULL);
		i++;
	}
	i = 0;
	free(philos_pthread);
}

int main(int ac, char **av)
{
	t_philo	*philos;

	if (ac != 5 && ac != 6)
		return (1);
	philos = set_up_philos(av);
	if (!philos)
	{
		;//return (free_all(&common_data))
	}
	g_stop = -1;
	run_simulation(philos);
	
	free(philos->forks);
	free(philos);
	return (0);
}

//./philosophers_42 10 20 10 4