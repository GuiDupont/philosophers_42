# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/25 11:29:54 by gdupont           #+#    #+#              #
#    Updated: 2021/04/30 15:42:58 by gdupont          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers_42

CC = gcc 

FLAGS = -Wall -Wextra -Werror

DEBUG = -g

PATH_SRCS = srcs

SRCS_LIST = philosophers_42.c tools.c logs.c time.c setup.c philos.c watcher.c
					
SRCS = $(addprefix ${PATH_SRCS}/, ${SRCS_LIST})

OBJS = $(SRCS:.c=.o)

INCLUDES = -pthread

FFLAGS = -g3 -fsanitize=address

$(NAME) :	$(OBJS) 
	$(CC) $(DEBUG) $(FLAGS) -g3 $(NOFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) 

all : $(NAME)

%.o: %.c
	@$(CC) -g3 $(DEBUG) $(FLAGS) $(NOFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

