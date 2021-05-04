/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_42.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:05:30 by gdupont           #+#    #+#             */
/*   Updated: 2021/05/04 10:32:54 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_42.h"

int		main(int ac, char **av)
{
	t_philo	philo;

	if (ac != 5 && ac != 6)
		return (1);
	set_up_philos(&philo, av);
	g_stop = -1;
	run_simulation(&philo);
	free_all(&philo);
	return (0);
}
