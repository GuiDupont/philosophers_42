#include "../includes/Philosophers_42.h"

void	launch_philo(pthread_t *philos_pthread, int begin, t_philo *philos)
{
	while (begin < philos->nb_philo)
	{
		philos[begin].last_time_eat = g_beginning;
		pthread_create(&philos_pthread[begin], NULL, eat_sleep_think, &philos[begin]);
		begin += 2;
	}
}

void	run_simulation(t_philo *philos)
{
	int i;
	pthread_t *philos_pthread;
	int	nb_philo;

	nb_philo = philos[0].nb_philo;
	philos_pthread = malloc(sizeof(*philos_pthread) * (nb_philo + 1));
	g_beginning = get_time_in_milli();
	launch_philo(philos_pthread, 0, philos);
	launch_philo(philos_pthread, 1, philos);
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

int		free_n_exit(t_philo *philos, int exit_value)
{
	free(philos);
	return (exit_value);
}

int main(int ac, char **av)
{
	t_philo	*philos;

	if (ac != 5 && ac != 6)
		return (1);
	philos = set_up_philos(av);
	if (!philos)
		return (1);
	g_stop = -1;
	run_simulation(philos);
	free(philos->forks);
	free(philos);
	return (0);
}

//./philosophers_42 10 20 10 4