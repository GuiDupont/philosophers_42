# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/25 11:29:54 by gdupont           #+#    #+#              #
#    Updated: 2021/01/19 14:38:43 by gdupont          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers_42

CC = gcc

FLAGS = -Wall -Wextra -Werror

PATH_SRCS = srcs

SRCS_LIST = philosophers_42.c tools.c
					
SRCS = $(addprefix ${PATH_SRCS}/, ${SRCS_LIST})

OBJS = $(SRCS:.c=.o)

INCLUDES = -pthread

SGFLAGS = -g ulimit -c unlimited

FFLAGS = -g3 -fsanitize=address

$(NAME) :	$(OBJS) 
	$(CC) $(FLAGS) $(FFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) 

all : $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) $(FFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

