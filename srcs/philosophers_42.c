#include "../includes/Philosophers_42.h"

void	eat(t_philo *philo)
{
	int min_fork;
	int max_fork;

	min_fork = get_min_fork(philo);
	max_fork = get_max_fork(philo);
	pthread_mutex_lock(&philo->common_data->forks[min_fork]);
	if (philo->common_data->stop != -1)
		return ;
	printf("%lld %d has taken a fork\n", get_time_in_milli() - philo->common_data->beginning, philo->id + 1);
	pthread_mutex_lock(&philo->common_data->forks[max_fork]);
	if (philo->common_data->stop != -1)
		return ;
	printf("%lld %d has taken a fork\n", get_time_in_milli() - philo->common_data->beginning, philo->id + 1);
	philo->last_time_eat = get_time_in_milli();
	if (philo->common_data->stop != -1)
		return ;
	printf("%lld %d is eating\n", get_time_in_milli() - philo->common_data->beginning, philo->id + 1);
	if (philo->common_data->stop != -1)
		return ;
	usleep(philo->common_data->time_to_eat);
	pthread_mutex_unlock(&philo->common_data->forks[min_fork]);
	pthread_mutex_unlock(&philo->common_data->forks[max_fork]);
}

void 	*eat_sleep_think(void *philo_void)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo*)philo_void;
	i = 0;
	while (i != philo->common_data->nb_time_to_eat && philo->common_data->stop == -1)
	{
		if (philo->common_data->stop != -1)
			return (NULL);
		eat(philo);
		if (philo->common_data->stop != -1)
			return (NULL);
		printf("%lld %d is sleeping\n", get_time_in_milli() - philo->common_data->beginning, philo->id + 1);
		if (philo->common_data->stop != -1)
			return (NULL);
		usleep(philo->common_data->time_to_sleep);
		if (philo->common_data->stop != -1)
			return (NULL);
		printf("%lld %d is thinking\n", get_time_in_milli() - philo->common_data->beginning, philo->id + 1);
		i++;
	}
	return (NULL);
}

int		set_up_common_data(int ac, char **av, t_data *common_data)
{
	common_data->nb_philo = atoi(av[1]);
	common_data->time_to_die = atoi(av[2]);
	common_data->time_to_eat = atoi(av[3]) * 1000;
	common_data->time_to_sleep = atoi(av[4]) * 1000;
	if (ac == 6)
		common_data->nb_time_to_eat = atoi(av[5]);
	else
		common_data->nb_time_to_eat = -1;
	common_data->stop = -1;
	return (1);
}


int		set_up_mutex(t_data *data)
{
	int i;

	data->forks = malloc(sizeof(*data->forks) * (data->nb_philo + 1));
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->nb_philo)
    {
        pthread_mutex_init(&data->forks[i], NULL);
		//add_security
		i++;
    }
	return (1);
}

t_philo	*set_up_philos(t_data *data)
{
	t_philo	*philos;
	int i;

	philos = malloc(sizeof(*philos) * data->nb_philo);
	//add_security;
	i = 0;
	while (i < data->nb_philo)
	{
		philos[i].id = i;
		philos[i].common_data = data;
		i++;
	}
	return (philos);
}

void	*watch_death(void *philos)
{
	t_philo	*philo;
	long long diff;
	long time_to_die;

	philo = (t_philo*)philos;
	time_to_die = philo[0].common_data->time_to_die;
	while (philo[0].common_data->stop == -1)
	{
		diff = get_time_in_milli() - philo[0].last_time_eat;
		if (diff >= time_to_die)
		{
			philo[0].common_data->stop = philo[0].id;
			printf("%lld %d hasn't eat for %lld milliseconds, he died %lld millisecondes ago\n", get_time_in_milli() - philo->common_data->beginning, philo->id + 1, diff, diff - philo->common_data->time_to_die);
			break ;
		}
		//printf("diff = %lld and time to die = %ld\n", diff, philo[0].common_data->time_to_die);
		usleep(5000);
	}
	return (NULL);
}

int	launch_watcher(t_philo *philos)
{
	pthread_t watcher;

	pthread_create(&watcher, NULL, watch_death, philos);
	return (1);
}

void	run_simulation(t_philo *philos)
{
	int i;
	pthread_t *philos_pthread;
	int	nb_philo;

	nb_philo = philos[0].common_data->nb_philo;
	philos_pthread = malloc(sizeof(*philos_pthread) * (nb_philo + 1));
	philos->common_data->beginning = get_time_in_milli();
	i = 0;
	while (i < nb_philo)
	{
		philos[i].last_time_eat = get_time_in_milli();
		pthread_create(&philos_pthread[i], NULL, eat_sleep_think, &philos[i]);
		launch_watcher(&philos[i]);
		i++;
	}
	i = 0;
	launch_watcher(philos);
	pthread_join(philos_pthread[0], NULL);
	printf("%lld %d died\n", get_time_in_milli() - philos->common_data->beginning, philos->common_data->stop + 1);
	i = 0;
	while (i < nb_philo)
	{
		pthread_detach(philos_pthread[i]);
		i++;
	}
}


int main(int ac, char **av)
{
	t_data	common_data;
	t_philo	*philos;

	if (ac != 5 && ac != 6)
		return (1);
	if (!set_up_common_data(ac, av, &common_data))
		return (1);
	if (!set_up_mutex(&common_data))
		return (1);
	philos = set_up_philos(&common_data);
	if (!philos)
	{
		;//return (free_all(&common_data))
	}
	run_simulation(philos);
	return (0);
}


//./philosophers_42 10 20 10 4