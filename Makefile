NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes -I $(MLXDIR)
LDFLAGS = -lm -L $(MLXDIR) -lmlx -lXext -lX11
SRC_DIR = srcs
OBJ_DIR = objs
MLXDIR = minilibx-linux
MLX = $(MLXDIR)/libmlx.a

SRC_FILES = main.c parser.c vector.c ray.c light.c color.c render.c scene.c mlx_display.c \
            objects/sphere.c objects/plane.c objects/cylinder.c
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_PATH = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

all: $(NAME)

$(MLX):
	@if [ ! -d "$(MLXDIR)" ]; then \
		echo "Cloning MiniLibX repository..."; \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLXDIR) >/dev/null 2>&1; \
	fi
	@echo "Compiling MiniLibX..."
	@make -s -C $(MLXDIR) >/dev/null 2>&1
	@echo "MiniLibX compiled."

$(NAME): $(MLX) $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_PATH) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@if [ -d "$(MLXDIR)" ]; then \
		make -s -C $(MLXDIR) clean >/dev/null 2>&1; \
	fi

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLXDIR)

re: fclean all

.PHONY: all clean fclean re