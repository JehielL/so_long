#include "so_long.h"

void load_texture(game_t *game, texture_t *texture, const char *file) {
    texture->img = mlx_xpm_file_to_image(game->mlx, (char *)file, &texture->width, &texture->height);
    if (!texture->img) {
        ft_printf("Failed to load texture: %s\n", file);
        error_exit("Error loading texture.");
    }
}
