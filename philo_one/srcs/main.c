/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:12:14 by gdupont           #+#    #+#             */
/*   Updated: 2021/04/21 10:27:45 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_42.h"

void	free_pthread(pthread_t *p, pthread_t *w, int nb)
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
}

int		free_n_exit(t_philo *philos, int exit_value)
{
	free(philos->forks);
	free(philos->print);
	free(philos);
	return (exit_value);
}

int		main(int ac, char **av)
{
	t_philo	*philos;

	if (ac != 5 && ac != 6)
		return (1);
	philos = set_up_philos(av);
	if (!philos)
		return (1);
	g_stop = -1;
	run_simulation(philos);
	return (free_n_exit(philos, 0));
}
