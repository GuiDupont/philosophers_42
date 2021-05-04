/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:05:06 by gdupont           #+#    #+#             */
/*   Updated: 2021/05/04 11:07:24 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_42.h"

void	*watch_death(void *philo_void)
{
	t_philo		*philo;
	long long	diff;
	long long	now;

	philo = (t_philo*)philo_void;
	while (g_stop == -1)
	{
		now = get_time_in_milli();
		diff = now - philo->last_time_eat;
		if (diff >= philo->time_to_die && philo->nb_time_to_eat != -2)
		{
			sem_wait(philo->print);
			g_stop = philo->id;
			printf("%lld %d died\n", get_time_in_milli()
			- g_beginning, philo->id + 1);
			sem_post(philo->kill);
			return (NULL);
		}
		else if (philo->meals == philo->nb_time_to_eat && g_stop == -1)
			return (NULL);
	}
	return (NULL);
}
