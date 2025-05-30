NAME =			miniRT
#LIBFTDIR =		src/libft
MLXDIR =		src/minilibx
OBJ_DIR =		obj
#LIBFT = $(LIBFTDIR)/libft.a
MLX =			$(MLXDIR)/libmlx.a
CC =			cc
CFLAGS =		-Wall -Wextra -Werror -g -fsanitize=address
#LIBS = -L$(LIBFTDIR) -lft -L$(MLXDIR) -lmlx -lXext -lX11 -lm
INCLUDES =		-Iincludes -I$(MLXDIR) #-I$(LIBFTDIR)
SRC_FILES =		main parser vector ray light color render \
            		objects/sphere objects/plane objects/cylinder
SRC = 			$(addsuffix .c, $(addprefix srcs/, $(SRC_FILES)))
OBJ =			$(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

#$(LIBFT):
#    @$(MAKE) -C $(LIBFTDIR)

$(MLX):
	@if [ ! -d "$(MLXDIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLXDIR); \
	fi
	@make -C $(MLXDIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(MAKE) -C $(MLXDIR) clean
	@rm -rf $(OBJ_DIR)
#    @$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(NAME)
 #   @$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re