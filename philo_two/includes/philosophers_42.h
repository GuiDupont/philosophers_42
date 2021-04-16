/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_42.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:30:37 by gdupont           #+#    #+#             */
/*   Updated: 2021/04/16 14:32:28 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_42_H
# define PHILOSOPHERS_42_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <string.h>

int				g_stop;
long long		g_beginning;

# define FORK_SEM "/forks"
# define PRINT_SEM "/print"
# define TAKING_SEM "/taking"

typedef struct	s_philo
{
	int				id;
	int				nb_philo;
	int				nb_time_to_eat;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	long long		last_time_eat;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*taking_fork;

}				t_philo;

long long		tv_to_milli(struct timeval *tv);
long long		get_time_in_milli(void);
void			precise_sleep(long long time);

void			print_log(unsigned long time, int id, char *log, t_philo *p);

char			*ft_strcpy(char *dest, char *src);
int				ft_strlen(const char *str);

t_philo			*set_up_philos(char **av);

int				launch_watcher(t_philo *philos);
void			*watch_death(void *philo);

void			eat(t_philo *philo);
void			*eat_sleep_think(void *philo_void);

void			free_all(t_philo *p, sem_t *f, sem_t *pr, sem_t *tk);

#endif
