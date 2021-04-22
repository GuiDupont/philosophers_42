#include "../includes/Philosophers_42.h"

void	launch_philo(int begin, t_philo *philos, int *philos_pid)
{
	int pid;
	pthread_t watcher_death;
	pthread_t watcher_eaten;

	if (!g_beginning)
		g_beginning = get_time_in_milli();
	while (begin < philos->nb_philo)
	{
		philos[begin].last_time_eat = g_beginning;
		pid = fork();
		if (!pid)
		{
			launch_watcher(&philos[begin], &watcher_death, &watcher_eaten);
			eat_sleep_think(&philos[begin]);
			pthread_detach(watcher_death);
			pthread_detach(watcher_eaten);
			//sem_post(philos->eaten);
			exit(g_stop);
		}
		philos_pid[begin] = pid;
		begin += 1;
	}
}

// void	wait_for_child()
// {
// 	while (i++ < philos->nb_philo)
// 	{
// 		waitpid(-1, &status, WUNTRACED);
// 		if (WEXITSTATUS(status) != 255)
// 		{
// 			kill(-1, SIGCHLD);
// 			break;
// 		}
// 	}
// }


void	*wait_eaten(void *sem_eat, int nb_philos)
{
	while (nb_philos--)
		sem_wait(sem_eat);
	return (NULL);
}

void	run_simulation(t_philo *philos)
{
	int *philo_pids;

	philo_pids = malloc(sizeof(int) * philos->nb_philo);
	launch_philo(0, philos, philo_pids);
	//launch_philo(1, philos, philo_pids);
	wait_eaten(philos->eaten, philos->nb_philo);
	free(philo_pids);
	return ;
}

int main(int ac, char **av)
{
	t_philo	*philos;

	if (ac != 5 && ac != 6)
		return (1);
	philos = set_up_philos(av);
	if (!philos)
		return (1);
	g_stop = -1;
	run_simulation(philos);
	free_all(philos);
	return (0);
}
