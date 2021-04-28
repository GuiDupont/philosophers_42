/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:43:21 by gdupont           #+#    #+#             */
/*   Updated: 2021/04/28 18:17:38 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_42.h"

void	free_all(t_philo *philos)
{
	free_all_sem(philos[1].forks, philos[1].print, philos[1].taking_fork);
	free(philos);
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
	return (0);
}
