# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: noa <noa@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/17 14:09:00 by noa               #+#    #+#              #
#    Updated: 2023/06/21 15:24:42 by nomoulin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = get_params main monitor_1 monitor_2 monitor_3 monitor_4 \
		philo_attr_1 philo_attr_2 philo_attr_3 philo_machine \
		philo utils_1 utils_2

OBJS = $(addsuffix .o, $(SRCS))

CC = clang

CFLAGS = -Wall -Wextra -Werror

LINKS = -lpthread

NAME = philo

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LINKS)

%.o : srcs/%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
