#include "../includes/Philosophers_42.h"

void	launch_philo(int begin, t_philo *philos, int *philos_pid)
{
	int pid;

	while (begin < philos->nb_philo)
	{
		philos[begin].last_time_eat = g_beginning;
		pid = fork();
		if (!pid)
		{
			launch_watcher(philos);
			eat_sleep_think(&philos[begin]);
			exit(0);
		}
		philos_pid[begin] = pid;
		begin += 2;
	}
}

void	run_simulation(t_philo *philos)
{
	int status;
	int *philo_pids;

	g_beginning = get_time_in_milli();
	philo_pids = malloc(sizeof(int) * philos->nb_philo);
	launch_philo(0, philos, philo_pids);
	launch_philo(1, philos, philo_pids);
	philos->philo_pid = philo_pids;
	waitpid(0, &status, 0);
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
	sem_close(philos->forks);
	sem_close(philos->print);
	free(philos);
	return (0);
}
