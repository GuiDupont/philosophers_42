/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:03:12 by gdupont           #+#    #+#             */
/*   Updated: 2021/04/16 14:03:13 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_42.h"

int		get_min_fork(t_philo *philo)
{
	int forks[2];
	int min_fork;
	int nb_philo;

	nb_philo = philo->nb_philo;
	forks[0] = (philo->id) % (nb_philo + 1);
	forks[1] = (philo->id + 1) % (nb_philo);
	min_fork = get_min(forks[0], forks[1]);
	return (min_fork);
}

int		get_max_fork(t_philo *philo)
{
	int forks[2];
	int max_fork;
	int nb_philo;

	nb_philo = philo->nb_philo;
	forks[0] = (philo->id) % (nb_philo + 1);
	forks[1] = (philo->id + 1) % (nb_philo);
	max_fork = get_max(forks[0], forks[1]);
	return (max_fork);
}
