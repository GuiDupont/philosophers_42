/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:03:32 by gdupont           #+#    #+#             */
/*   Updated: 2021/04/29 09:37:36 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_42.h"

static	int	nb_length(unsigned long n)
{
	int	count;

	count = 1;
	while (n >= 10)
	{
		n = n / 10;
		count = count + 1;
	}
	return (count);
}

static	int	ft_itoa_on_buffer(unsigned long timestamp, char *str)
{
	int nb_len;
	int index;

	nb_len = nb_length(timestamp);
	index = --nb_len;
	while (nb_len >= 0)
	{
		str[nb_len] = timestamp % 10 + '0';
		timestamp /= 10;
		nb_len--;
	}
	return (index);
}

void		print_log(long long time, int id, char *log, t_philo *phi)
{
	char		str[100];
	int			index;

	if (g_stop != -1)
		return ;
	pthread_mutex_lock(phi->print);
	if (!time)
		time = get_time_in_milli() - g_beginning;
	else
		time -= g_beginning;
	index = ft_itoa_on_buffer(time, str);
	index++;
	str[index++] = ' ';
	index += ft_itoa_on_buffer(id, &str[index]);
	index++;
	str[index++] = ' ';
	ft_strcpy(&str[index], log);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(phi->print);
}
