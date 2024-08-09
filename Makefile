# Nombre del ejecutable
NAME        = so_long

# Compilador y flags
CC          = gcc
FLAGS       = -Wall -Wextra -Werror -g -fsanitize=address
MLX_DIR     = minilibx-linux
LFT         = utils/libft/libft.a
INC         = -I ./utils/libft -I ./minilibx-linux
LIB         = -L ./utils/libft -lft -L ./minilibx-linux -lmlx -lXext -lX11 -lm -lz

# Archivos fuente y objetos
SRC         = src/so_long.c src/game.c src/map.c src/render.c src/textures.c
OBJ         = $(SRC:src/%.c=obj/%.o)

# Regla principal
all:        $(MLX_DIR)/libmlx.a $(LFT) obj $(NAME)
		@echo " [ OK ] | Todos los componentes se han compilado con exito!"

# Compilar el ejecutable
$(NAME):    $(OBJ)
		$(CC) $(FLAGS) -o $@ $^ $(LIB)
		@echo " [ OK ] | Ejecutable $(NAME) Construido con exito!"

# Compilar MinilibX
$(MLX_DIR)/libmlx.a:
		@echo " [ .. ] | Compilando minilibx.."
		@make -s -C $(MLX_DIR)
		@echo " [ OK ] | Minilibx compilada con exito!"

# Compilar libft
$(LFT):
		@echo " [ .. ] | Compilando libft.."
		@make -s -C utils/libft
		@echo " [ OK ] | Libft compilada con exito!"

# Crear directorio de objetos
obj:
		@mkdir -p obj

# Regla para compilar cada archivo fuente en objeto
obj/%.o: src/%.c
		$(CC) $(FLAGS) $(INC) -c $< -o $@
		@echo " [ OK ] | Compiled $<"

# Limpiar archivos objetos y ejecutable
clean:
		@make -s clean -C utils/libft
		@rm -rf $(OBJ) obj
		@echo " [ OK ] | Archivos Objeto removidos con exito."

fclean: clean
		@make -s clean -C $(MLX_DIR)
		@rm -rf $(NAME)
		@echo " [ OK ] | Binary file removed."

# Recompilar todo
re: fclean all

.PHONY: all clean fclean re
