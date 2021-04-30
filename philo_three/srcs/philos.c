#include "../includes/Philosophers_42.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->taking_fork);
	sem_wait(philo->forks);
	print_log(get_time_in_milli(), philo->id + 1, "has taken a fork\n", philo);
	sem_wait(philo->forks);
	print_log(get_time_in_milli(), philo->id + 1, "has taken a second fork\n", philo);
	sem_post(philo->taking_fork);
	philo->last_time_eat = get_time_in_milli();
	print_log(philo->last_time_eat, philo->id + 1, "is eating\n", philo);
	precise_sleep(philo->time_to_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
	if (g_stop != -1)
			return ;	
}

void 	*eat_sleep_think(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo*)philo_void;
	philo->last_time_eat = g_beginning;
	philo->meals = 0;
	while (philo->meals != philo->nb_time_to_eat && g_stop == -1)
	{
		eat(philo);
		print_log(get_time_in_milli(), philo->id + 1, "is sleeping\n", philo);
		if (g_stop != -1)
			break;
		precise_sleep(philo->time_to_sleep);
		print_log(get_time_in_milli(), philo->id + 1, "is thinking\n", philo);
		philo->meals++;
	}
	if (g_stop == -1)
		g_stop = -2;
	return (NULL);
}
