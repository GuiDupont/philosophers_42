/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:21:32 by gdupont           #+#    #+#             */
/*   Updated: 2021/05/03 11:32:12 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_42.h"

void	*watch_death(void *philo_void)
{
	t_philo		*philos;
	long long	diff;
	long long	now;

	while (g_stop == -1)
	{
		philos = (t_philo*)philo_void;
		now = get_time_in_milli();
		diff = now - philos->last_time_eat;
		if ((diff >= philos->time_to_die && philos->nb_time_to_eat != -2)
		|| g_stop != -1)
		{
			if (g_stop == -1)
				print_log(now, philos->id + 1, "died\n", philos);
			g_stop = philos->id;
			break ;
		}
	}
	return (NULL);
}
