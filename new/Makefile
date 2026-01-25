# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 13:04:48 by tozaki            #+#    #+#              #
#    Updated: 2026/01/22 13:04:49 by tozaki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
SRCS	=	launch_threads.c\
			main.c\
			philo_action.c\
			philo_finish.c\
			raise_error.c\
			routines.c\
			set_argv.c\
			set_malloc.c\
			set_mutex.c\
			set_threads_info.c\
			time_utils.c
OBJS	=	$(SRCS:%.c=%.o)
# vpath %c ./philo

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJS)

.PHONY: fclean
fclean: clean
	rm -rf $(TARGET)

.PHONY: re
re: fclean all
