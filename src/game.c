#include "so_long.h"

void error_exit(const char *message) {
    printf("Error\n%s\n", message);
    exit(EXIT_FAILURE);
}

int key_press(int keycode, game_t *game) {
    int new_x = game->player_x;
    int new_y = game->player_y;

    if (keycode == 53 || keycode == 65307) // ESC key
        exit(0);
    else if (keycode == 119) // W key
        new_y--;
    else if (keycode == 97) // A key
        new_x--;
    else if (keycode == 115) // S key
        new_y++;
    else if (keycode == 100) // D key
        new_x++;

    if (new_x >= 0 && new_x < game->map_width && new_y >= 0 && new_y < game->map_height) {
        if (game->map[new_y][new_x] != '1') {
            if (game->map[new_y][new_x] == 'C') {
                game->collected++;
                if (game->collected == game->collectables) {
                    printf("Haz coleccionado todos los items!\n");
                }
            }
            if (game->map[new_y][new_x] == 'E' && game->collected == game->collectables) {
                printf("You won!\n");
                exit(0);
            }

            game->map[game->player_y][game->player_x] = '0';
            game->player_x = new_x;
            game->player_y = new_y;
            game->map[game->player_y][game->player_x] = 'P';
            game->moves++;
            printf("Movimientos realizados: %d\n", game->moves);

            mlx_clear_window(game->mlx, game->win);
            draw_map(game); // Necesitarás incluir render.c o su prototipo aquí
        }
    }

    return (0);
}
