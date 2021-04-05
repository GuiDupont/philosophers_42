#include "../includes/Philosophers_42.h"

void	eat(t_philo *philo)
{
	int forks[2];
	int min_fork;
	int max_fork;
	int nb_philo;

	nb_philo = philo->common_data->nb_philo;
	forks[0] = (philo->id) % (nb_philo + 1);
	forks[1] = (philo->id + 1) % (nb_philo);
	min_fork = get_min(forks[0], forks[1]);
	max_fork = get_max(forks[0], forks[1]);
	pthread_mutex_lock(&philo->common_data->forks[min_fork]);
	printf("%ld %d has taken a fork\n", get_time_in_milli() - philo->common_data->beginning, philo->id);
	pthread_mutex_lock(&philo->common_data->forks[max_fork]);
	printf("%ld %d has taken a fork\n", get_time_in_milli() - philo->common_data->beginning, philo->id);
	printf("%ld %d is eating\n", get_time_in_milli() - philo->common_data->beginning, philo->id);
	philo->last_time_eat = get_time_in_milli();
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
	while (i != philo->common_data->nb_time_to_eat && !philo->common_data->stop)
	{
		if (philo->common_data->stop)
			break ;
		eat(philo);
		if (philo->common_data->stop)
			break ;
		printf("%ld %d is sleeping\n", get_time_in_milli() - philo->common_data->beginning, philo->id);
		usleep(philo->common_data->time_to_sleep);
		if (philo->common_data->stop)
			break ;
		printf("%ld %d is thinking\n", get_time_in_milli() - philo->common_data->beginning, philo->id);
		i++;
	}
	return (NULL);
}

int		set_up_common_data(int ac, char **av, t_data *common_data)
{
	common_data->nb_philo = atoi(av[1]);
	common_data->time_to_die = atoi(av[2]) * 1000;
	common_data->time_to_eat = atoi(av[3]) * 1000;
	common_data->time_to_sleep = atoi(av[4]) * 1000;
	if (ac == 6)
		common_data->nb_time_to_eat = atoi(av[5]);
	else
		common_data->nb_time_to_eat = -1;
	common_data->stop = 0;
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
		philos[i].last_time_eat = 0;
		philos[i].common_data = data;
		i++;
	}
	return (philos);
}

void	*watch_death(void *philos)
{
	t_philo	*philo;
	int	i;
	long diff;

	philo = (t_philo*)philos;
	i = 0;
	while (i < philo[0].common_data->nb_philo)
	{
		diff = get_time_in_milli() - philo[i].last_time_eat;
		if (diff >= philo[0].common_data->time_to_die)
		{
			philo[i].common_data->stop = i;
			printf("diff = %ld\n", diff);
			
			printf("\n%ld = time of death\n", get_time_in_milli() - diff);

			break ;
		}
		printf("diff = %ld\n", diff);
		i++;
		if (i == philo[0].common_data->nb_philo)
			i = 0;
	}
	return (NULL);
}

int	launch_watcher(t_philo *philos)
{
	int	retval;
	int *ptr_retval;
	pthread_t watcher;

	ptr_retval = &retval;
	pthread_create(&watcher, NULL, watch_death, philos);
	pthread_join(watcher, (void**)&(ptr_retval));

	pthread_detach(watcher);
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
		pthread_create(&philos_pthread[i], NULL, eat_sleep_think, &philos[i]);
		i++;
	}
	i = 0;
	launch_watcher(philos);
	pthread_join(philos_pthread[0], NULL);
	printf("%ld %d died\n", get_time_in_milli() - philos->common_data->beginning, philos->common_data->stop);
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


// int main(int ac, char **av)
// {
// 	struct timeval tv;
// 	long begin;
// 	pthread_t *philos;
// 	int i;
// 	int nb_philo;
// 	long	time_to_die;
// 	long	time_to_sleep;
// 	long	time_to_eat;
// 	int		nb_time_to_eat;

// 	if (ac != 5 && ac != 6)
// 		return (1);
// 	nb_philo = atoi(av[1]);
// 	time_to_die = atoi(av[2]);
// 	time_to_eat = atoi(av[3]);
// 	time_to_sleep = atoi(av[4]);
// 	if (ac == 6)
// 		nb_time_to_eat = atoi(av[5]);	
// 	data = malloc(sizeof(*data) * (nb_philo + 1));

// 	i = 1;
// 	forks = malloc(sizeof(*forks) * (nb_philo + 1));


// 	while (i <= nb_philo)
//     {
//         pthread_mutex_init(&forks[i], NULL);
// 		i++;
//     }
// 	i = 1;
// 	while (i <= nb_philo)
// 	{
// 		gettimeofday(&tv, NULL);
// 		data[i].begin = tv_to_milli(&tv);
// 		data[i].id = i;
// 		data[i].round = nb_philo;
// 		data[i].time_to_die = time_to_die;
// 		data[i].time_to_sleep = time_to_sleep;
// 		data[i].time_to_eat = time_to_eat;
// 		data[i].nb_philo = nb_philo;
// 		pthread_create(&philos[i], NULL, eat_sleep_think, &data[i]);
// 		i++;
// 	}
// 	i = 1;
// 	while (i <= nb_philo)
// 	{
// 		pthread_join(philos[i], NULL);
// 		i++;
// 	}
// 	i = 1;
	
	
// 	// printf("programme started at %ld millisecondes\n", begin);
// 	// sleep(1);
// 	// gettimeofday(&tv, NULL);
// 	// printf("%ld millisecondes past\n", tv_to_milli(&tv) - begin);
	
// }