/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:21:32 by gdupont           #+#    #+#             */
/*   Updated: 2021/04/16 14:22:16 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_42.h"

void	*watch_death(void *philo_void)
{
	int			i;
	t_philo		*philos;
	long long	diff;
	long long	now;

	i = 0;
	philos = (t_philo*)philo_void;
	while (i < philos->nb_philo)
	{
		now = get_time_in_milli();
		diff = now - philos[i].last_time_eat;
		if (diff >= philos->time_to_die && philos[i].nb_time_to_eat != -2)
		{
			print_log(now, philos->id + 1, "died\n", philos);
			g_stop = philos[0].id;
			pthread_mutex_lock(philos->print);
			break ;
		}
		i++;
		if (i == philos->nb_philo)
			i = 0;
	}
	return (NULL);
}
