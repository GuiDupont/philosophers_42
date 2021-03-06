/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:11:47 by gdupont           #+#    #+#             */
/*   Updated: 2021/04/29 10:26:09 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_42.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->min_fork]);
	print_log(0, philo->id + 1, "has taken a fork\n", philo);
	pthread_mutex_lock(&philo->forks[philo->max_fork]);
	print_log(0, philo->id + 1, "has taken a second fork\n", philo);
	philo->last_time_eat = get_time_in_milli();
	print_log(philo->last_time_eat, philo->id + 1, "is eating\n", philo);
	precise_sleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->forks[philo->min_fork]);
	pthread_mutex_unlock(&philo->forks[philo->max_fork]);
}

void		*eat_sleep_think(void *philo_void)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo*)philo_void;
	i = 0;
	while (i != philo->nb_time_to_eat && g_stop == -1)
	{
		eat(philo);
		print_log(0, philo->id + 1, "is sleeping\n", philo);
		precise_sleep(philo->time_to_sleep);
		print_log(0, philo->id + 1, "is thinking\n", philo);
		i++;
	}
	philo->nb_time_to_eat = -2;
	return (NULL);
}
