#include "../includes/Philosophers_42.h"

void	*kill_all(void *philo_void)
{
	int i;
	t_philo *philo;
	i = -1;

	philo = (t_philo*) philo_void;
	sem_wait(philo->kill);
	g_stop = -2;
	while (++i < philo->nb_philo)
		kill(philo->pid[i], SIGKILL);
	return (NULL);
}

void	launch_philo(int i, t_philo *philo)
{
	pthread_t actions;
	pthread_t watcher;

	if (!g_beginning)
		g_beginning = get_time_in_milli();
	philo->last_time_eat = g_beginning;
	while (i < philo->nb_philo)
	{
		philo->pid[i] = fork();
		if (!philo->pid[i])
		{
			philo->id = i;
			pthread_create(&actions, NULL, eat_sleep_think, philo);
			pthread_create(&watcher, NULL, watch_death, philo);
			pthread_join(watcher, NULL);
			if (philo->meals == philo->nb_time_to_eat)
			{
				pthread_join(actions, NULL);
				free_all(philo);
				exit(1);
			}
			exit(0);
		}
		else if (philo->pid[i] == -1)
		{
			printf("Could not fork\n");
			exit(1);
		}
		i += 1;
	}
}

void	waiting(t_philo *philo)
{
	int i;
	int status;

	i = -1;
	while (++i < philo->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 0)
		{
			i = -1;
			while (++i < philo->nb_philo)
				kill(philo->pid[i], SIGKILL);
			free_all(philo);
			break ;
		}
		if (i == philo->nb_philo && philo->nb_time_to_eat != -1)
		{
			sem_wait(philo->print);
			break ;
		}
	}
}

void	run_simulation(t_philo *philo)
{
	pthread_t killer;

	philo->pid = malloc(sizeof(int) * philo->nb_philo);
	launch_philo(0, philo);
	pthread_create(&killer, NULL, kill_all, philo);
	waiting(philo);
	if (g_stop == -1)
		sem_post(philo->kill);
	free_all(philo);
	pthread_detach(killer);
}


int main(int ac, char **av)
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
