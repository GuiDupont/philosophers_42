# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/25 11:29:54 by gdupont           #+#    #+#              #
#    Updated: 2021/04/21 10:09:42 by gdupont          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers_42

CC = gcc

FLAGS = -Wall -Wextra -Werror

PATH_SRCS = srcs

SRCS_LIST = main.c tools.c logs.c time.c forks.c setup.c philos.c watcher.c tools_2.c run_simulation.c
					
SRCS = $(addprefix ${PATH_SRCS}/, ${SRCS_LIST})

OBJS = $(SRCS:.c=.o)

INCLUDES = -pthread

SGFLAGS = -g ulimit -c unlimited

$(NAME) :	$(OBJS) 
	$(CC) $(FLAGS) $(FFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) 

all : $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

