/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 10:30:59 by gdupont           #+#    #+#             */
/*   Updated: 2021/05/04 10:33:02 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_42.h"

void	*kill_all(void *philo_void)
{
	int		i;
	t_philo *philo;

	i = -1;
	philo = (t_philo*)philo_void;
	sem_wait(philo->kill);
	g_stop = -2;
	while (++i < philo->nb_philo)
		kill(philo->pid[i], SIGKILL);
	return (NULL);
}

void	philos_thread_launch(pthread_t *todo, pthread_t *watcher, t_philo *p)
{
	pthread_create(todo, NULL, eat_sleep_think, p);
	pthread_create(watcher, NULL, watch_death, p);
	pthread_join(*watcher, NULL);
	if (p->meals == p->nb_time_to_eat)
	{
		pthread_join(*todo, NULL);
		free_all(p);
		exit(1);
	}
	exit(0);
}

void	launch_philo(t_philo *philo)
{
	pthread_t	todo;
	pthread_t	watcher;
	int			i;

	if (!g_beginning)
		g_beginning = get_time_in_milli();
	philo->last_time_eat = g_beginning;
	i = 0;
	while (i < philo->nb_philo)
	{
		philo->pid[i] = fork();
		if (!philo->pid[i])
		{
			philo->id = i;
			philos_thread_launch(&todo, &watcher, philo);
		}
		else if (philo->pid[i] == -1)
		{
			printf("Could not fork\n");
			exit(1);
		}
		i += 1;
	}
}

void	waiting(t_philo *philo)
{
	int i;
	int status;

	i = -1;
	while (++i < philo->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 0)
		{
			i = -1;
			while (++i < philo->nb_philo)
				kill(philo->pid[i], SIGKILL);
			free_all(philo);
			break ;
		}
		if (i == philo->nb_philo && philo->nb_time_to_eat != -1)
		{
			sem_wait(philo->print);
			break ;
		}
	}
}

void	run_simulation(t_philo *philo)
{
	pthread_t	killer;

	philo->pid = malloc(sizeof(int) * philo->nb_philo);
	launch_philo(philo);
	pthread_create(&killer, NULL, kill_all, philo);
	waiting(philo);
	if (g_stop == -1)
		sem_post(philo->kill);
	pthread_join(killer, NULL);
	free_all(philo);
}
