#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define TILE_SIZE 40

typedef struct {
    void *img;
    int width;
    int height;
} texture_t;

typedef struct {
    void *mlx;
    void *win;
    int player_x;
    int player_y;
    int collectables;
    int collected;
    int moves;
    int map_width;
    int map_height;
    char **map;
    texture_t wall_texture;
    texture_t player_texture;
    texture_t collectable_texture;
    texture_t exit_texture;
    texture_t empty_texture;
} game_t;

void error_exit(const char *message) {
    printf("Error\n%s\n", message);
    exit(EXIT_FAILURE);
}

void draw_texture(game_t *game, int x, int y, texture_t texture) {
    mlx_put_image_to_window(game->mlx, game->win, texture.img, x * TILE_SIZE, y * TILE_SIZE);
}

void draw_map(game_t *game) {
    for (int y = 0; y < game->map_height; y++) {
        for (int x = 0; x < game->map_width; x++) {
            if (game->map[y][x] == '1')
                draw_texture(game, x, y, game->wall_texture); // Paredes
            else if (game->map[y][x] == 'P')
                draw_texture(game, x, y, game->player_texture); // Jugador
            else if (game->map[y][x] == 'C')
                draw_texture(game, x, y, game->collectable_texture); // Coleccionables
            else if (game->map[y][x] == 'E')
                draw_texture(game, x, y, game->exit_texture); // Salida
            else
                draw_texture(game, x, y, game->empty_texture); // Espacios en blanco
        }
    }
}

int key_press(int keycode, game_t *game) {
    int new_x = game->player_x;
    int new_y = game->player_y;

    if (keycode == 53 || keycode == 65307) // Tecla 'ESC' en MacOS y Linux
        exit(0);
    else if (keycode == 119) // Tecla 'W'
        new_y--;
    else if (keycode == 97) // Tecla 'A'
        new_x--;
    else if (keycode == 115) // Tecla 'S'
        new_y++;
    else if (keycode == 100) // Tecla 'D'
        new_x++;

    // Verificar colisiones
    if (new_x >= 0 && new_x < game->map_width && new_y >= 0 && new_y < game->map_height) {
        if (game->map[new_y][new_x] != '1') {
            if (game->map[new_y][new_x] == 'C') {
                game->collected++;
                if (game->collected == game->collectables) {
                    printf("¡Has recogido todos los objetos!\n");
                }
            }
            if (game->map[new_y][new_x] == 'E' && game->collected == game->collectables) {
                printf("¡Has ganado!\n");
                exit(0);
            }

            game->map[game->player_y][game->player_x] = '0'; // Espacio vacío
            game->player_x = new_x;
            game->player_y = new_y;
            game->map[game->player_y][game->player_x] = 'P'; // Jugador
            game->moves++;
            printf("Movimientos: %d\n", game->moves);

            // Redibujar el mapa
            mlx_clear_window(game->mlx, game->win);
            draw_map(game);
        }
    }

    return (0);
}

char **read_map(const char *filename, int *width, int *height) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_exit("No se pudo abrir el archivo del mapa.");

    char **map = NULL;
    char buffer[1024];
    int bytes_read;
    int line_count = 0;
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        char *line = strtok(buffer, "\n");
        while (line) {
            if (!map)
                map = malloc(sizeof(char *));
            else
                map = realloc(map, (line_count + 1) * sizeof(char *));
            if (!map)
                error_exit("Error de asignación de memoria.");
            map[line_count] = strdup(line);
            if (!map[line_count])
                error_exit("Error de asignación de memoria.");
            line_count++;
            line = strtok(NULL, "\n");
        }
    }
    close(fd);

    *height = line_count;
    *width = line_count > 0 ? strlen(map[0]) : 0;
    return map;
}

void free_map(char **map, int height) {
    if (!map)
        return;
    for (int i = 0; i < height; i++) {
        free(map[i]);
    }
    free(map);
}

void validate_map(game_t *game) {
    if (!game->map || game->map_height == 0 || game->map_width == 0)
        error_exit("Mapa no válido.");
    int player_count = 0;
    int exit_count = 0;
    game->collectables = 0;
    for (int y = 0; y < game->map_height; y++) {
        if (strlen(game->map[y]) != game->map_width)
            error_exit("El mapa no es rectangular.");
        for (int x = 0; x < game->map_width; x++) {
            if (game->map[y][x] == 'P') {
                player_count++;
                game->player_x = x;
                game->player_y = y;
            } else if (game->map[y][x] == 'E') {
                exit_count++;
            } else if (game->map[y][x] == 'C') {
                game->collectables++;
            } else if (game->map[y][x] != '0' && game->map[y][x] != '1') {
                error_exit("Carácter desconocido en el mapa.");
            }
        }
    }
    if (player_count != 1 || exit_count != 1 || game->collectables < 1)
        error_exit("El mapa debe tener un jugador, una salida y al menos un coleccionable.");
    for (int x = 0; x < game->map_width; x++) {
        if (game->map[0][x] != '1' || game->map[game->map_height - 1][x] != '1')
            error_exit("El mapa debe estar rodeado de muros.");
    }
    for (int y = 0; y < game->map_height; y++) {
        if (game->map[y][0] != '1' || game->map[y][game->map_width - 1] != '1')
            error_exit("El mapa debe estar rodeado de muros.");
    }
}

void load_texture(game_t *game, texture_t *texture, const char *file) {
    texture->img = mlx_xpm_file_to_image(game->mlx, (char *)file, &texture->width, &texture->height);
    if (!texture->img) {
        printf("No se pudo cargar la textura: %s\n", file);
        error_exit("Error al cargar la textura.");
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Uso: %s <map_file>\n", argv[0]);
        return (1);
    }

    game_t game;
    game.mlx = mlx_init();
    if (!game.mlx)
        error_exit("No se pudo inicializar mlx.");

    game.map = read_map(argv[1], &game.map_width, &game.map_height);
    validate_map(&game);

    game.win = mlx_new_window(game.mlx, game.map_width * TILE_SIZE, game.map_height * TILE_SIZE, "So Long");
    if (!game.win)
        error_exit("No se pudo crear la ventana.");

    load_texture(&game, &game.wall_texture, "wall_texture.xpm");
    load_texture(&game, &game.player_texture, "player_texture.xpm");
    load_texture(&game, &game.collectable_texture, "collectable_texture.xpm");
    load_texture(&game, &game.exit_texture, "exit_texture.xpm");
    load_texture(&game, &game.empty_texture, "empty_texture.xpm");

    draw_map(&game);

    mlx_key_hook(game.win, key_press, &game);
    mlx_loop(game.mlx);

    free_map(game.map, game.map_height);
    return (0);
}
