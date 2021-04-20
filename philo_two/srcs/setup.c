/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:46:50 by gdupont           #+#    #+#             */
/*   Updated: 2021/04/20 16:46:31 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_42.h"

static	int	check_arg(char **av)
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

static void	fill_philos_data(char **av, t_philo *philos, int i)
{
	philos->id = i + 1;
	philos->last_time_eat = 0;
	philos->nb_philo = ft_atoi(av[1]);
	philos->time_to_eat = ft_atoi(av[3]);
	philos->time_to_sleep = ft_atoi(av[4]);
	philos->time_to_die = ft_atoi(av[2]);
	if (av[5])
		philos->nb_time_to_eat = ft_atoi(av[5]);
	else
		philos->nb_time_to_eat = -1;
}

static void	set_up_sem(int nb_philo, sem_t **f, sem_t **p, sem_t **t)
{
	sem_unlink(FORK_SEM);
	sem_unlink(PRINT_SEM);
	sem_unlink(TAKING_SEM);
	*f = sem_open(FORK_SEM, O_CREAT, S_IRWXU, nb_philo);
	*p = sem_open(PRINT_SEM, O_CREAT, S_IRWXU, 1);
	*t = sem_open(TAKING_SEM, O_CREAT, S_IRWXU, nb_philo - 1);
}

t_philo			*set_up_philos(char **av)
{
	t_philo			*philos;
	sem_t			*forks;
	int				i;
	sem_t			*print;
	sem_t			*taking_fork;

	if (!check_arg(av))
		return (NULL);
	philos = malloc(sizeof(*philos) * ft_atoi(av[1]));
	set_up_sem(ft_atoi(av[1]), &forks, &print, &taking_fork);
	if (!philos || !forks || !print || !taking_fork)
	{
		free_all(philos);
		printf("Can't allocate memory or setup sem properly\n");
		return (NULL);
	}
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		fill_philos_data(av, &philos[i], i);
		philos[i].forks = forks;
		philos[i].print = print;
		philos[i++].taking_fork = taking_fork;
	}
	return (philos);
}
