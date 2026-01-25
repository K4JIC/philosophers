NAME	=	philo
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
SRCS	=	launch_threads.c\
			main.c\
			philo_action.c\
			philo_action_utils.c\
			philo_finish.c\
			raise_error.c\
			philo_routines.c\
			grim_routines.c\
			set_argv.c\
			set_malloc.c\
			set_mutex.c\
			set_threads_info.c\
			time_utils.c
OBJS	=	$(SRCS:%.c=%.o)
HDRS	=	philo.h
# vpath %c ./philo

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS) $(HDRS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all
