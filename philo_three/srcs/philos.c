#include "../includes/Philosophers_42.h"

void	eat(t_philo *philo)
{
	usleep(200);
	sem_wait(philo->forks);
	print_log(get_time_in_milli(), philo->id + 1, "has taken a fork\n", philo);
	sem_wait(philo->forks);
	print_log(get_time_in_milli(), philo->id + 1, "has taken a fork\n", philo);
	philo->last_time_eat = get_time_in_milli();
	print_log(philo->last_time_eat, philo->id + 1, "is eating\n", philo);
	usleep(philo->time_to_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
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
