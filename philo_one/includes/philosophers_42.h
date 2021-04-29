/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_42.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:57:09 by gdupont           #+#    #+#             */
/*   Updated: 2021/04/29 10:04:27 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_42_H
# define PHILOSOPHERS_42_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

int				g_stop;
long long		g_beginning;

typedef struct	s_philo
{
	int				id;
	int				nb_philo;
	int				min_fork;
	int				max_fork;
	int				nb_time_to_eat;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	long long		last_time_eat;
	pthread_mutex_t *forks;
	pthread_mutex_t *print;
}				t_philo;

long long		tv_to_milli(struct timeval *tv);
long long		get_time_in_milli(void);
void			precise_sleep(long long time);

int				get_min_fork(t_philo *philo);
int				get_max_fork(t_philo *philo);

void			print_log(long long time, int id, char *log, t_philo *phi);

char			*ft_strcpy(char *dest, char *src);
int				ft_strlen(const char *str);
int				get_min(int a, int b);
int				get_max(int a, int b);
int				ft_atoi(const char *str);
void			ft_swap(int *a, int *b);

t_philo			*set_up_philos(char **av);
void			*watch_death(void *philo);
void			run_simulation(t_philo *philos);
void			*eat_sleep_think(void *philo_void);
void			free_pthread(pthread_t *p, pthread_t *w, int nb);

#endif
