/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:27:23 by gdupont           #+#    #+#             */
/*   Updated: 2021/04/21 17:30:50 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers_42.h"

void	*ft_exit(void *data)
{
	exit(1);
}

int main()
{
	pthread_t exit;

	pthread_create(&exit, NULL, ft_exit(), NULL);
	sleep(20);
	return(0);
}