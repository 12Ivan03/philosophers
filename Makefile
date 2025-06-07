CC = cc
CFLAGS = -I./include -Wall -Wextra -Werror
CLIB = -c

BUILD_PATH = ./build

SRC_FILES = ./main.c \
			./utils.c \
			./check_argv.c \
			./init_mutex.c \
			./declaration_manager.c \
			./declaration_philosophers.c \
			./create_threads.c \
			./routine.c \
			./routine_helper.c \
			./grim_onlooker.c \
			./grim_routine.c \
			./get_time_of_day.c \
			./printf_error.c \
			./join_threads.c \
			./free/clear_mutex.c \
			./get_info_mutex.c


OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_FILES := $(OBJ_FILES:%=$(BUILD_PATH)/%)

NAME = philo

all: $(NAME)

$(BUILD_PATH)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o  $@

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
