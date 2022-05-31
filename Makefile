# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsung <rsung@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 11:15:29 by rsung             #+#    #+#              #
#    Updated: 2022/05/31 10:56:34 by rsung            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = $(addprefix srcs/,main.c init.c utils.c routine.c routine_utils.c \
utils2.c)

OBJS = $(SRCS:.c=.o)

HEADER = ./include

CC = gcc

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@ -I $(HEADER)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) -pthread $(OBJS) -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
