NAME = philo

SRC = main.c threads.c struct.c actions.c utils.c

CC = gcc
CFLAGS = -pthread -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC)
	@echo "\n\033[32m\_@-@_/ PHILO COMPILED \_@-@_/\n"

clean:
		@rm -f $(NAME)
		@echo "\n\033[31m\_@-@_/ DELETING EVERYTHING \_@-@_/\n"

fclean:	clean

re:	fclean all

.PHONY: all clean fclean re