/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:29:34 by gdupont           #+#    #+#             */
/*   Updated: 2021/04/20 17:28:33 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_42.h"

static void	free_pthread(pthread_t *p, pthread_t *w, int nb)
{
	int i;

	i = -1;
	while (++i < nb)
	{
		pthread_detach(w[i]);
		pthread_detach(p[i]);
	}
	free(w);
	free(p);
	printf("we jsut free pthread malloc and detach\n");
}

void			free_all_sem(sem_t *f, sem_t *pr, sem_t *tk)
{
	printf("we are about to unlink\n");
	sem_close(f);
	sem_unlink(FORK_SEM);
	sem_close(pr);
	sem_unlink(PRINT_SEM);
	sem_close(tk);
	sem_unlink(TAKING_SEM);
}

static void	launch_philo(pthread_t *philos_pthread, int i, t_philo *philos)
{
	if (!g_beginning)
		g_beginning = get_time_in_milli();
	while (i < philos->nb_philo)
	{
		philos[i].last_time_eat = g_beginning;
		pthread_create(&philos_pthread[i], NULL, eat_sleep_think, &philos[i]);
		i += 2;
	}
}

void		run_simulation(t_philo *philos)
{
	int			i;
	pthread_t	*philos_pthread;
	int			nb_philo;
	pthread_t	*watcher_pthread;

	nb_philo = philos[0].nb_philo;
	philos_pthread = malloc(sizeof(*philos_pthread) * (nb_philo + 1));
	watcher_pthread = malloc(sizeof(*watcher_pthread) * (nb_philo + 1));
	launch_philo(philos_pthread, 0, philos);
	usleep(1000);
	launch_philo(philos_pthread, 1, philos);
	i = 0;
	while (i < nb_philo)
	{
		pthread_create(&watcher_pthread[i], NULL, watch_death, &philos[i]);
		pthread_join(philos_pthread[i], NULL);
		i++;
	}
	free_pthread(philos_pthread, watcher_pthread, philos->nb_philo);
	free_all(philos);
}
