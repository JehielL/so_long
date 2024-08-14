#include "so_long.h"

void error_exit(const char *message) {
    ft_printf("Error\n%s\n", message);
    exit(EXIT_FAILURE);
}

int handle_key_press(int keycode, game_t *game) {
    int new_x = game->player_x;
    int new_y = game->player_y;

    if (keycode == 53 || keycode == 65307) { // ESC key
        close_game(game);
    } else if (keycode == 119) { // W key
        new_y--;
    } else if (keycode == 97) { // A key
        new_x--;
    } else if (keycode == 115) { // S key
        new_y++;
    } else if (keycode == 100) { // D key
        new_x++;
    }

    process_movement(new_x, new_y, game);
    return (0);
}

void process_movement(int new_x, int new_y, game_t *game) {
    if (new_x >= 0 && new_x < game->map_width && new_y >= 0 && new_y < game->map_height) {
        char cell = game->map[new_y][new_x];
        if (cell != '1') { // No es una pared
            if (cell == 'E' && game->collected == game->total_collectables) { 
                ft_printf("¡Has ganado!\n");
                close_game(game);
            }
            if (cell == 'C') {
                game->collected++;
                if (game->collected == game->total_collectables) {
                    ft_printf("¡Has coleccionado todos los ítems!\n");
                }
            }
            game->map[game->player_y][game->player_x] = '0';
            game->player_x = new_x;
            game->player_y = new_y;
            game->map[game->player_y][game->player_x] = 'P';
            game->moves++;
            ft_printf("Movimientos realizados: %d\n", game->moves);
            mlx_clear_window(game->mlx, game->win);
            draw_map(game);
        }
    }
}
