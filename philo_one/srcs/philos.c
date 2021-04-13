#include "../includes/Philosophers_42.h"

void	eat(t_philo *philo)
{
	usleep(200);
	pthread_mutex_lock(&philo->forks[philo->min_fork]);
	print_log(get_time_in_milli(), philo->id + 1, "has taken a fork\n", philo);
	pthread_mutex_lock(&philo->forks[philo->max_fork]);
	print_log(get_time_in_milli(), philo->id + 1, "has taken a fork\n", philo);
	philo->last_time_eat = get_time_in_milli();
	print_log(philo->last_time_eat, philo->id + 1, "is eating\n", philo);
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->forks[philo->min_fork]);
	pthread_mutex_unlock(&philo->forks[philo->max_fork]);
}

void 	*eat_sleep_think(void *philo_void)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo*)philo_void;
	i = 0;
	philo->last_time_eat = g_beginning;
	while (i != philo->nb_time_to_eat && g_stop == -1)
	{
		eat(philo);
		print_log(get_time_in_milli(), philo->id + 1, "is sleeping\n", philo);
		usleep(philo->time_to_sleep);
		print_log(get_time_in_milli(), philo->id + 1, "is thinking\n", philo);
		i++;
	}
	philo->nb_time_to_eat = -2;
	return (NULL);
}
