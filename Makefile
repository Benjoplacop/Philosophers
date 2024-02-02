SRC = main.c init.c thread.c utils_philo.c libft_utils.c mutex.c

INCLUDE = philosophers.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror

FLAG_THREAD = -lpthread

NAME = philo

OBJSRC = ${SRC:.c=.o}

all: ${NAME}

${NAME}:${OBJSRC}
		${CC} ${OBJSRC} ${INCLUDE} -o ${NAME} ${FLAG_THREAD}

clean: 
		@rm -f *.o
		@echo "Remove .o"

fclean: clean
		@rm -f ${NAME}
		@echo "Remove ./philo"

re: fclean all
