#include "../includes/Philosophers_42.h"

// void	*watch_eaten(void *philos)
// {
// 	t_philo *philo;
	
// 	philo = (t_philo*)philos;
// 	sem_wait(philo->stop);
// 	if (g_stop == -1)
// 		g_stop = -2;
// 	sem_wait(philo->print);
// 	sem_post(philo->print);
// 	return (NULL);
// }

void	*watch_death(void *philo_void)
{
	t_philo		*philo;
	long long	diff;
    long long	now;

	philo = (t_philo*)philo_void;
	while (g_stop == -1)
	{
        now = get_time_in_milli();
		diff = now - philo->last_time_eat;
		if (diff >= philo->time_to_die && philo->nb_time_to_eat != -2)
		{

			sem_wait(philo->print);
			g_stop = philo->id;	
			printf("%lld %d has died\n", get_time_in_milli() - g_beginning, philo->id);
			sem_post(philo->kill);
			return (NULL) ;
		}
		else if (philo->meals == philo->nb_time_to_eat && g_stop == -1)
			return (NULL) ;
	}

	return (NULL);
}