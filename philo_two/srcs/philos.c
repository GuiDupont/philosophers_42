/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:42:16 by gdupont           #+#    #+#             */
/*   Updated: 2021/04/20 16:08:53 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_42.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->taking_fork);
	sem_wait(philo->forks);
	print_log(0, philo->id, "has taken a fork\n", philo);
	sem_wait(philo->forks);
	print_log(0, philo->id, "has taken a second fork\n", philo);
	sem_post(philo->taking_fork);
	philo->last_time_eat = get_time_in_milli();
	print_log(philo->last_time_eat, philo->id, "is eating\n", philo);
	precise_sleep(philo->time_to_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	*eat_sleep_think(void *philo_void)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo*)philo_void;
	i = 0;
	while (i != philo->nb_time_to_eat && g_stop == -1)
	{
		eat(philo);
		print_log(0, philo->id, "is sleeping\n", philo);
		precise_sleep(philo->time_to_sleep);
		print_log(0, philo->id, "is thinking\n", philo);
		i++;
	}
	philo->nb_time_to_eat = -2;
	return (NULL);
}
