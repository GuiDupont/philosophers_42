/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:14:59 by gdupont           #+#    #+#             */
/*   Updated: 2021/05/04 11:12:49 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_42.h"

static	int		check_arg(char **av)
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

static	void	fork_repartition(t_philo *philos, int i)
{
	//philos->min_fork = get_min_fork(philos);
	//philos->max_fork = get_max_fork(philos);
	philos->min_fork = i;
	philos->max_fork = i + 1;
	if (i == philos->nb_philo - 1)
	{
		philos->max_fork = 0;
		ft_swap(&philos->min_fork, &philos->max_fork);
	}
	if (philos->nb_philo % 2 && philos->id == philos->nb_philo - 1)
		ft_swap(&philos->min_fork, &philos->max_fork);
	if (philos->nb_philo % 2 && philos->id % 2)
		ft_swap(&philos->min_fork, &philos->max_fork);
}

static	void	fill_philos_data(char **av, t_philo *philos, int i)
{
	philos->id = i;
	philos->last_time_eat = 0;
	philos->nb_philo = ft_atoi(av[1]);
	philos->time_to_eat = ft_atoi(av[3]);
	philos->time_to_sleep = ft_atoi(av[4]);
	philos->time_to_die = ft_atoi(av[2]);
	if (av[5])
		philos->nb_time_to_eat = ft_atoi(av[5]);
	else
		philos->nb_time_to_eat = -1;
	fork_repartition(philos, i);
}

static	void	free_all(t_philo *p, pthread_mutex_t *f, pthread_mutex_t *pr)
{
	free(p);
	free(f);
	free(pr);
}

pthread_mutex_t	*set_up_mutex(int nb_philo)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(*forks) * nb_philo);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

t_philo			*set_up_philos(char **av)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				i;
	pthread_mutex_t *print;

	if (!check_arg(av))
		return (NULL);
	philos = malloc(sizeof(*philos) * atoi(av[1]));
	forks = set_up_mutex(atoi(av[1]));
	print = malloc(sizeof(*print));
	if (!philos || !forks || !print)
	{
		free_all(philos, forks, print);
		printf("Can't allocate memory or setup mutex properly\n");
		return (NULL);
	}
	pthread_mutex_init(print, NULL);
	i = 0;
	while (i < atoi(av[1]))
	{
		fill_philos_data(av, &philos[i], i);
		philos[i].forks = forks;
		philos[i++].print = print;
	}
	return (philos);
}
