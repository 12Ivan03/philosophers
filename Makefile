CC = cc
CFLAGS = -Wall -Wextra -Werror
CLIB = -c

SRC_FILES = ./main.c \
			./utils.c \
			./check_argv.c \
			./init_mutex.c \
			./declaration_manager.c \
			./declaration_philosophers.c \
			./create_threads.c \
			./routine.c \
			./grim_onlooker.c 


OBJ_FILES = $(SRC_FILES:.c=.o)

NAME = philo

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(CLIB) $^ -o $@

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)

clean:
	rm -f $(OBJ_FILES)

fclean : clean
	rm -f $(NAME)

re: clean fclean all

.PHONY: clean fclean all
