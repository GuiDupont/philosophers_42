/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:50:18 by gdupont           #+#    #+#             */
/*   Updated: 2021/04/19 12:08:06 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_42.h"

char	*ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	precise_sleep(long long time)
{
	long long start;

	start = get_time_in_milli();
	while (get_time_in_milli() - start < time)
		usleep(400);
}

int		ft_atoi(const char *str)
{
	int		n;
	int		negative;
	long	result;

	negative = 1;
	n = 0;
	result = 0;
	while (str[n] == ' ' || str[n] == '\n' || str[n] == '\t' || str[n] == '\v'
	|| str[n] == '\f' || str[n] == '\r')
		n++;
	if (str[n] == '-' || str[n] == '+')
	{
		if (str[n] == '-')
			negative = -negative;
		n++;
	}
	while (str[n] >= '0' && str[n] <= '9')
		result = result * 10 + (str[n++] - '0');
	if (result < 0 && negative > 0)
		return (-1);
	else if (result < 0 && negative < 0 && result * negative != -2147483648)
		return (0);
	return (result * negative);
}
