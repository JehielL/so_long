# Nombre del ejecutable
NAME        = so_long

# Compilador y flags
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g -fsanitize=address
MLX_DIR     = minilibx-linux
LFT_DIR     = utils/libft
GN_DIR      = utils/gnl
INC         = -I ./utils/libft -I ./minilibx-linux -I ./utils/gnl
LIB         = -L ./utils/libft -lft -L ./minilibx-linux -lmlx -lXext -lX11 -lm -lz

# Archivos fuente y objetos
SRC         = src/so_long.c src/game.c src/map.c src/render.c src/textures.c \
              $(GN_DIR)/get_next_line.c $(GN_DIR)/get_next_line_utils.c
OBJ         = $(SRC:.c=.o)

# Regla principal
all:        $(NAME)

# Compilar el ejecutable
$(NAME):    $(OBJ)
		@echo " [ .. ] | Compilando MinilibX.."
		@make -C $(MLX_DIR)
		@echo " [ .. ] | Compilando libft.."
		@make -C $(LFT_DIR)
		$(CC) $(CFLAGS) -o $@ $^ $(LIB)
		@echo " [ OK ] | Ejecutable $(NAME) construido con éxito!"

# Regla para compilar cada archivo fuente en objeto
%.o: %.c
		@mkdir -p obj
		$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Limpiar archivos objetos y ejecutable
clean:
		@make -C $(LFT_DIR) clean
		@rm -f $(OBJ)
		@echo " [ OK ] | Archivos objeto eliminados."

fclean: clean
		@make -C $(MLX_DIR) clean
		@rm -f $(NAME)
		@echo " [ OK ] | Ejecutable eliminado."

# Recompilar todo
re: fclean all

.PHONY: all clean fclean re
