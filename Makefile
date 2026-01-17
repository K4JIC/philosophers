TARGET	=	philo
CC		=	cc
FLAGS	=	-Wall -Werror -Wextra
SRCS	=	launch_threads.c\
			main.c\
			philo.h\
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
VPATH	=	SRCS:./philo

.PHONY: all
all:$(TARGET)

$(TARGET):
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@
