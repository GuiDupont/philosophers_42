#include "../includes/Philosophers_42.h"

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
