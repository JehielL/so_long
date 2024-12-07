
NAME        = so_long

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g3 -fsanitize=address
MLX_DIR     = minilibx-linux
LFT_DIR     = utils/libft
GN_DIR      = utils/gnl
FT_PRINTF   = utils/ft_printf_42
INC         = -I ./utils/libft -I ./minilibx-linux -I ./utils/gnl
LIB         = -L ./utils/libft -lft -L ./minilibx-linux -lmlx -lXext -lX11 -lm -lz

GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m
CHECK_MARK  = \033[1;32m✔\033[0m

SRC         = src/so_long.c src/game.c src/map.c src/render.c src/textures.c src/inspects.c\
              $(GN_DIR)/get_next_line.c $(GN_DIR)/get_next_line_utils.c $(FT_PRINTF)/ft_printf.c  \
              $(FT_PRINTF)/ft_aux_pf.c $(FT_PRINTF)/ft_putchar_pf.c $(FT_PRINTF)/ft_puthex_pf.c $(FT_PRINTF)/ft_putnbr_pf.c \
              $(FT_PRINTF)/ft_putptr_pf.c $(FT_PRINTF)/ft_putstr_pf.c $(FT_PRINTF)/ft_putuint_pf.c 
OBJ         = $(SRC:.c=.o)

all:        $(NAME)

$(NAME):    $(OBJ)
		@echo " [ .. ] | Compiling MinilibX.."
		@make -C $(MLX_DIR) > /dev/null
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) MinilibX Compiled succesfull!$(RESET)"
		@echo " [ .. ] | Compiling  libft.."
		@make -C $(LFT_DIR) > /dev/null
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) libft Compiled succesfull!$(RESET)"
		@echo " [ .. ] | Compiling GNL.."
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) GNL Compiled succesfull!$(RESET)"
		@echo " [ .. ] | Compiling ft_printf.."
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) ft_printf Compiled succesfull!$(RESET)"
		@$(CC) $(CFLAGS) -o $@ $^ $(LIB)
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) Your Game: $(NAME) Compiled succesfull!$(RESET)"
%.o: %.c
		@$(CC) $(CFLAGS) $(INC) -c $< -o $@ > /dev/null
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) Compiled: $<$(RESET)"

clean:
		@make -C $(LFT_DIR) clean > /dev/null
		@rm -f $(OBJ)
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) Objects Deleted.$(RESET)"

fclean: clean
		@make -C $(MLX_DIR) clean > /dev/null
		@rm -f $(NAME)
		@echo " $(RED)[ OK ] $(CHECK_MARK) Game: $(NAME) Deleted.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
