NAME = philo

INCLUDES    = -I./includes
HEADER      = ./includes/philo.h

CC          = clang
FLAGS       = -Wall -Wextra -Werror -fsanitize=thread

SRC  = main.c philo.c parsing.c utils.c init.c forks.c routine.c \

BUILD_DIR   = build
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJ) -o $(NAME)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re build
