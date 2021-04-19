/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:50:59 by gdupont           #+#    #+#             */
/*   Updated: 2021/04/19 12:12:59 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_42.h"

void	*watch_death(void *philo)
{
	int			i;
	t_philo		*philos;
	long long	diff;
	long long	now;

	i = 0;
	philos = (t_philo*)philo;
	while (i < philos->nb_philo)
	{
		now = get_time_in_milli();
		diff = now - philos[i].last_time_eat;
		if (diff >= philos->time_to_die && philos[i].nb_time_to_eat != -2)
		{
			print_log(now, philos->id + 1, "died\n", philo);
			g_stop = philos[0].id;
			break ;
		}
		i++;
		if (i == philos->nb_philo)
			i = 0;
	}
	return (NULL);
}

int		launch_watcher(t_philo *philos)
{
	pthread_t watcher;

	pthread_create(&watcher, NULL, watch_death, philos);
	return (1);
}
