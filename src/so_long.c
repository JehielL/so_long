#include "so_long.h"

int close_game(game_t *game) {
    printf("Juego cerrado con exito\n");  // Mensaje al cerrar la ventana
    free_map(game->map, game->map_height);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    exit(0);
    return (0);
}
static int validate(char *file)
{
    int len = 0;
    len = ft_strlen(file);

    if(ft_strcmp(file + len - 5, "/.ber") == 0)
        return(0);
    if(ft_strcmp(file + len - 4, ".ber") == 0)
        return (1);
    return (0);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        ft_printf("Usage: %s <map_file>\n", argv[0]);
        return (1);
    }

    game_t game;
    game.mlx = mlx_init();
    if(validate(argv[1]) == 0)
        error_exit("map is invalid. its neccesary .ber extension");
        
    if (!game.mlx)
        error_exit("Failed to initialize mlx.");
    game.map = read_map(argv[1], &game.map_width, &game.map_height);
    validate_map(&game);

    game.win = mlx_new_window(game.mlx, game.map_width * TILE_SIZE, game.map_height * TILE_SIZE, "So Long");
    if (!game.win)
        error_exit("Failed to create window.");

    load_texture(&game, &game.wall_texture, "textures/wall_texture.xpm");
    load_texture(&game, &game.player_texture, "textures/player_texture.xpm");
    load_texture(&game, &game.collectable_texture, "textures/collectable_texture.xpm");
    load_texture(&game, &game.exit_texture, "textures/exit_texture.xpm");
    load_texture(&game, &game.empty_texture, "textures/empty_texture.xpm");
    draw_map(&game);
    // Actualiza la llamada para manejar la entrada de teclado
    mlx_key_hook(game.win, handle_key_press, &game);

    // Hook para manejar el evento de cerrar la ventana (clic en la "X")
    mlx_hook(game.win, 17, 0, (int (*)(void *))close_game, &game);

    mlx_loop(game.mlx);

    free_map(game.map, game.map_height);
    return (0);
}
