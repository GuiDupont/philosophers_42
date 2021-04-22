/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:27:23 by gdupont           #+#    #+#             */
/*   Updated: 2021/04/21 17:33:57 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers_42.h"

void	*ft_last(void *data)
{
	(void)data;
	sleep(20);
	return (NULL);
}


void	*ft_exit(void *data)
{
	(void)data;
	exit(0);
}

int main()
{
	pthread_t exit;
	pthread_t last;

	pthread_create(&last, NULL, ft_last, NULL);
	pthread_create(&exit, NULL, ft_exit, NULL);
	sleep(20);
	return(0);
}