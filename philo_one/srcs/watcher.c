/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:21:32 by gdupont           #+#    #+#             */
/*   Updated: 2021/04/20 12:01:03 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_42.h"

// void	*watch_death(void *philo_void)
// {
// 	volatile int	i;
// 	t_philo		*philos;
// 	volatile long long	diff;
// 	volatile long long	now;

// 	i = 0;
// 	philos = (t_philo*)philo_void;
// 	while (i < philos->nb_philo)
// 	{
// 		now = get_time_in_milli();
// 		diff = now - philos[i].last_time_eat;
// 		if (diff >= philos->time_to_die && philos[i].nb_time_to_eat != -2)
// 		{
// 			if (philos[i].nb_time_to_eat == -2)
// 				printf("attention\n");
// 			else
// 				printf("diff = %lld parce que lasttime-eat = %lld et now = %lld\n", diff, philos->last_time_eat - g_beginning, now - g_beginning);
// 			print_log(now, philos->id + 1, "died\n", philos);
// 			g_stop = philos[0].id;
// 			pthread_mutex_lock(philos->print);
// 			break ;
// 		}
// 		i++;
// 		if (i == philos->nb_philo)
// 			i = 0;
// 		//usleep(700);
// 	}
// 	return (NULL);
// }

void	*watch_death(void *philo_void)
{
	t_philo		*philos;
	volatile long long	diff;
	volatile long long	now;

	while(1)
	{
		philos = (t_philo*)philo_void;
		now = get_time_in_milli();
		diff = now - philos->last_time_eat;
		if (diff >= philos->time_to_die && philos->nb_time_to_eat != -2)
		{
			pthread_mutex_lock(philos->print);
			printf("%lld %d died\n", now - g_beginning, philos->id + 1);
			g_stop = philos->id;
			//pthread_mutex_unlock(philos->print);
			break ;
		}
		else
			precise_sleep(9);
	}
	return (NULL);
}

