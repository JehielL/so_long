#include "so_long.h"

void draw_texture(game_t *game, int x, int y, texture_t texture) {
    mlx_put_image_to_window(game->mlx, game->win, texture.img, x * TILE_SIZE, y * TILE_SIZE);
}

void draw_map(game_t *game) {
    int x = 0;
    int y = 0;

    while (y < game->map_height) {
        x = 0; // Reiniciar x al comienzo de cada fila
        while (x < game->map_width) {
            if (game->map[y][x] == '1')
                draw_texture(game, x, y, game->wall_texture);
            else if (game->map[y][x] == 'P')
                draw_texture(game, x, y, game->player_texture);
            else if (game->map[y][x] == 'C')
                draw_texture(game, x, y, game->collectable_texture);
            else if (game->map[y][x] == 'E')
                draw_texture(game, x, y, game->exit_texture);
            else
                draw_texture(game, x, y, game->empty_texture);
            x++;
        }
        y++;
    }
}
