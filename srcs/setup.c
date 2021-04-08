#include "../includes/Philosophers_42.h"

t_philo	*set_up_philos(char **av)
{
	t_philo	*philos;
    pthread_mutex_t *forks;
	int i;

	philos = malloc(sizeof(*philos) * atoi(av[1]));
	//add_security;
    forks = set_up_mutex(atoi(av[1]));
	i = 0;
	while (i < atoi(av[1]))
	{
		philos[i].id = i;
        philos[i].nb_philo = atoi(av[1]);
		philos[i].min_fork = get_min_fork(&philos[i]);
		philos[i].max_fork = get_max_fork(&philos[i]);
		philos[i].time_to_eat = atoi(av[3]) * 1000;
		philos[i].time_to_sleep = atoi(av[4]) * 1000;
		philos[i].time_to_die = atoi(av[2]);
        if (av[5])
            philos[i].nb_time_to_eat = atoi(av[5]);
        else
            philos[i].nb_time_to_eat = -1;
        philos[i].forks = forks;
		i++;
	}
	return (philos);
}

pthread_mutex_t *set_up_mutex(int nb_philo)
{
	int             i;
    pthread_mutex_t *forks;

	forks = malloc(sizeof(*forks) * nb_philo);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < nb_philo)
    {
        pthread_mutex_init(&forks[i], NULL);
		//add_security
		i++;
    }
	return (forks);
}
