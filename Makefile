# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/04 10:38:21 by gdupont           #+#    #+#              #
#    Updated: 2021/05/04 10:48:00 by gdupont          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	make -C philo_one all
	make -C philo_two all
	make -C philo_three all

clean :
	make clean -s -C philo_one
	make clean -s -C philo_two
	make clean -s -C philo_three

fclean:
	make fclean -s -C philo_one
	make fclean -s -C philo_two
	make fclean -s -C philo_three
