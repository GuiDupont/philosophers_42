#include "../includes/Philosophers_42.h"

static	int 	check_arg(char **av)
{
	int i;
	int y;

	i = 1;
	while (av[i])
	{
		y = 0;
		while (av[i][y])
		{
			if (av[i][y] > '9' || av[i][y] < '0')
			{
				printf("Bad argument\n");
				return (0);
			}
			y++;
		}
		i++;
	}
	if (!atoi(av[1]) || atoi(av[1]) == 1)
	{
		printf("Bad argument\n");
		return (0);
	}
	return (1);
}

void	fill_philos_data(char **av, t_philo *philos, int i)
{
	philos->id = i;
	philos->last_time_eat = 0;
	philos->nb_philo = atoi(av[1]);
	philos->min_fork = get_min_fork(philos);
	philos->max_fork = get_max_fork(philos);
	philos->time_to_eat = atoi(av[3]) * 1000;
	philos->time_to_sleep = atoi(av[4]) * 1000;
	philos->time_to_die = atoi(av[2]);
	if (av[5])
		philos->nb_time_to_eat = atoi(av[5]);
	else
		philos->nb_time_to_eat = -1;
}

static sem_t *set_up_sem(int nb_philo)
{
	int             i;
    sem_t			*forks;

	forks = sem_open("/f", O_CREAT, S_IRWXU, 1);
	if (!forks)
		return (NULL);
	i = -1;
	while (++i < nb_philo)
        sem_post(forks);
	return (forks);
}

t_philo			*set_up_philos(char **av)
{
	t_philo			*philos;
    sem_t			*forks;
	int				i;

	if (!check_arg(av))
		return (NULL);
	philos = malloc(sizeof(*philos) * atoi(av[1]));
    forks = set_up_sem(atoi(av[1]));
	if (!philos || !forks)
	{
		free(philos);
		free(forks);
		printf("Can't allocate memory or setup sem properly\n");
		return (NULL);
	}
	i = 0;
	while (i < atoi(av[1]))
	{
		fill_philos_data(av, &philos[i], i);
        philos[i].forks = forks;
		i++;
	}
	return (philos);
}


