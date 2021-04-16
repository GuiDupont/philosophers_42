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
			launch_watcher(&philos[begin]);
			eat_sleep_think(&philos[begin]);
			exit(g_stop);
		}
		philos_pid[begin] = pid;
		begin += 2;
	}
}

void	kill_philos(int *philo_pid, int nb_philos, t_philo *philo)
{
	int i;

	i = 0;
	(void)philo;
	while (i < nb_philos)
	{
		kill(philo_pid[i], 9);
		i++;
	}
}

void	run_simulation(t_philo *philos)
{
	int status;
	int *philo_pids;
	int i;

	g_beginning = get_time_in_milli();
	philo_pids = malloc(sizeof(int) * philos->nb_philo);
	launch_philo(0, philos, philo_pids);
	usleep(1000);
	launch_philo(1, philos, philo_pids);
	philos->philo_pid = philo_pids;
	i = 0;
	while (i < philos->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != 255)
		{
			kill_philos(philo_pids, philos->nb_philo, philos);
			break ;
		}
		i++;
	}
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
	sem_close(philos->forks);
	sem_close(philos->print);
	free(philos);
	return (0);
}
