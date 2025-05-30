NAME = miniRT
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes -lmlx -framework OpenGL -framework AppKit
SRC_DIR = srcs
OBJ_DIR = objs
SRC_FILES = main.c parser.c vector.c ray.c light.c color.c render.c \
            objects/sphere.c objects/plane.c objects/cylinder.c
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_PATH = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

all: $(NAME)

$(NAME): $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_PATH)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re