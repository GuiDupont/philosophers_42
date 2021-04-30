/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:05:09 by gdupont           #+#    #+#             */
/*   Updated: 2021/04/30 15:22:32 by gdupont          ###   ########.fr       */
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

void		fill_philos_data(char **av, t_philo *p)
{
	p->last_time_eat = 0;
	p->nb_philo = ft_atoi(av[1]);
	p->time_to_eat = ft_atoi(av[3]);
	p->time_to_sleep = ft_atoi(av[4]);
	p->time_to_die = ft_atoi(av[2]);
	if (av[5])
		p->nb_time_to_eat = ft_atoi(av[5]);
	else
		p->nb_time_to_eat = -1;
	p->pid = NULL;
	sem_unlink(FORK_SEM);
	sem_unlink(PRINT_SEM);
	sem_unlink(TAKING_SEM);
	sem_unlink(KILL_SEM);
	p->forks = sem_open(FORK_SEM, O_CREAT | S_IRWXU, 0644, p->nb_philo);
	p->print = sem_open(PRINT_SEM, O_CREAT | S_IRWXU, 0644, 1);
	p->taking_fork = sem_open(TAKING_SEM, O_CREAT | S_IRWXU, 0644, 1);
	p->kill = sem_open(KILL_SEM, O_CREAT | S_IRWXU, 0644, 0);
}

void		free_all(t_philo *p)
{
	sem_close(p->forks);
	sem_unlink(FORK_SEM);
	sem_close(p->print);
	sem_unlink(PRINT_SEM);
	sem_close(p->taking_fork);
	sem_unlink(TAKING_SEM);
	sem_close(p->kill);
	sem_unlink(KILL_SEM);
	free(p->pid);
	p->pid = NULL;
}

void		set_up_philos(t_philo *philo, char **av)
{
	if (!check_arg(av))
		return ;
	fill_philos_data(av, philo);
	if (!philo->forks | !philo->print | !philo->taking_fork ||
	!philo->kill)
		ft_exit("Can't allocate memory or setup sem properly\n");
}
