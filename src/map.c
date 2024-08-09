#include "so_long.h"


void validate_map(game_t *game) {
    if (!game->map || game->map_height == 0 || game->map_width == 0)
        error_exit("Mapa no válido.");

    size_t y = 0;
    int player_count = 0;
    int exit_count = 0;
    game->collectables = 0;

    while (y < (size_t)game->map_height) {
        if ((size_t)strlen(game->map[y]) != (size_t)game->map_width)
            error_exit("El mapa no es rectangular.");

        size_t x = 0;
        while (x < (size_t)game->map_width) {
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
            x++;
        }
        y++;
    }

    if (player_count != 1 || exit_count != 1 || game->collectables < 1)
        error_exit("El mapa debe tener un jugador, una salida y al menos un coleccionable.");

    size_t x = 0;
    while (x < (size_t)game->map_width) {
        if (game->map[0][x] != '1' || game->map[game->map_height - 1][x] != '1')
            error_exit("El mapa debe estar rodeado de muros.");
        x++;
    }

    size_t height = 0;
    while (height < (size_t)game->map_height) {
        if (game->map[height][0] != '1' || game->map[height][game->map_width - 1] != '1')
            error_exit("El mapa debe estar rodeado de muros.");
        height++;
    }
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
            if (!map) {
                map = malloc(sizeof(char *));
            } else {
                map = realloc(map, (line_count + 1) * sizeof(char *));
            }
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
    
    int i = 0;
    while (i < height) {
        free(map[i]);
        i++;
    }
    free(map);
}

