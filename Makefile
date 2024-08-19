# Nombre del ejecutable
NAME        = so_long

# Compilador y flags
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g
MLX_DIR     = minilibx-linux
LFT_DIR     = utils/libft
GN_DIR      = utils/gnl
FT_PRINTF   = utils/ft_printf_42
INC         = -I ./utils/libft -I ./minilibx-linux -I ./utils/gnl
LIB         = -L ./utils/libft -lft -L ./minilibx-linux -lmlx -lXext -lX11 -lm -lz

# Colores
GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m
CHECK_MARK  = \033[1;32m✔\033[0m

# Archivos fuente y objetos
SRC         = src/so_long.c src/game.c src/map.c src/render.c src/textures.c \
              $(GN_DIR)/get_next_line.c $(GN_DIR)/get_next_line_utils.c $(FT_PRINTF)/ft_printf.c  \
              $(FT_PRINTF)/ft_aux_pf.c $(FT_PRINTF)/ft_putchar_pf.c $(FT_PRINTF)/ft_puthex_pf.c $(FT_PRINTF)/ft_putnbr_pf.c \
              $(FT_PRINTF)/ft_putptr_pf.c $(FT_PRINTF)/ft_putstr_pf.c $(FT_PRINTF)/ft_putuint_pf.c 
OBJ         = $(SRC:.c=.o)

# Regla principal
all:        $(NAME)

# Compilar el ejecutable
$(NAME):    $(OBJ)
		@echo " [ .. ] | Compilando MinilibX.."
		@make -C $(MLX_DIR) > /dev/null
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) MinilibX compilado con éxito!$(RESET)"
		@echo " [ .. ] | Compilando libft.."
		@make -C $(LFT_DIR) > /dev/null
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) libft compilado con éxito!$(RESET)"
		@echo " [ .. ] | Compilando GNL.."
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) GNL compilado con éxito!$(RESET)"
		@echo " [ .. ] | Compilando ft_printf.."
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) ft_printf compilado con éxito!$(RESET)"
		@$(CC) $(CFLAGS) -o $@ $^ $(LIB)
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) Ejecutable $(NAME) construido con éxito!$(RESET)"

# Regla para compilar cada archivo fuente en objeto
%.o: %.c
		@$(CC) $(CFLAGS) $(INC) -c $< -o $@ > /dev/null
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) Compilado: $<$(RESET)"

# Limpiar archivos objetos y ejecutable
clean:
		@make -C $(LFT_DIR) clean > /dev/null
		@rm -f $(OBJ)
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) Archivos objeto eliminados.$(RESET)"

fclean: clean
		@make -C $(MLX_DIR) clean > /dev/null
		@rm -f $(NAME)
		@echo " $(RED)[ OK ] Ejecutable $(NAME) eliminado.$(RESET)"

# Recompilar todo
re: fclean all

# Ejecutar el programa con Valgrind
valgrind: all
		@echo " [ .. ] | Ejecutando el programa con Valgrind.."
		@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(NAME)

.PHONY: all clean fclean re valgrind
