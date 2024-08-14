#include "so_long.h"

// Función recursiva para llenar el mapa
static void fill_recursive(char **tab, t_coordinates size, t_coordinates pos, char target) {
    t_coordinates next_pos;

    // Verificar si la posición está fuera de los límites
    if (pos.y < 0 || pos.y >= size.y || pos.x < 0 || pos.x >= size.x)
        return;

    // Verificar si la posición ya está marcada o no es del tipo objetivo
    if (tab[pos.y][pos.x] == 'F' || tab[pos.y][pos.x] != target)
        return;

    // Marcar la posición como accesible
    tab[pos.y][pos.x] = 'F';

    // Llamar recursivamente a las posiciones adyacentes
    next_pos = (t_coordinates){pos.x, pos.y - 1}; // Arriba
    fill_recursive(tab, size, next_pos, target);
    next_pos = (t_coordinates){pos.x, pos.y + 1}; // Abajo
    fill_recursive(tab, size, next_pos, target);
    next_pos = (t_coordinates){pos.x - 1, pos.y}; // Izquierda
    fill_recursive(tab, size, next_pos, target);
    next_pos = (t_coordinates){pos.x + 1, pos.y}; // Derecha
    fill_recursive(tab, size, next_pos, target);
}

// Función para iniciar el llenado desde una posición
static void flood_fill(char **tab, t_coordinates size, t_coordinates begin) {
    char target = tab[begin.y][begin.x];
    fill_recursive(tab, size, begin, target);
}

// Liberar la memoria duplicada del mapa
static void free_map_dup(char **map, int height) {
    int i = 0;
    while (i < height) {
        free(map[i]);
        i++;
    }
    free(map);
}

// Leer el mapa desde un archivo
static char **read_map_dup(const char *filename, int *width, int *height) {
    char **map;
    int fd, i = 0;
    char *line;

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error al abrir el archivo del mapa");
        return NULL;
    }

    map = malloc(sizeof(char *) * 1000); // Ajustar según necesidades
    if (!map) {
        perror("Error al asignar memoria para el mapa");
        close(fd);
        return NULL;
    }

    while ((line = get_next_line(fd)) != NULL) {
        int line_len = ft_strlen(line);
        map[i] = malloc(line_len + 1);
        if (!map[i]) {
            perror("Error al asignar memoria para una línea del mapa");
            free_map_dup(map, i);
            close(fd);
            return NULL;
        }
        strcpy(map[i], line);
        free(line);
        i++;
    }
    close(fd);

    *width = ft_strlen(map[0]);
    *height = i;
    return map;
}

// Encontrar la posición inicial del jugador
static t_coordinates find_starting_position(char **map, t_coordinates size) {
    t_coordinates pos;
    int row, col;

    pos.y = -1;
    pos.x = -1;
    row = 0;
    while (row < size.y) {
        col = 0;
        while (col < size.x) {
            if (map[row][col] == 'P') {
                pos.y = row;
                pos.x = col;
                return pos;
            }
            col++;
        }
        row++;
    }
    return pos;
}

// Encontrar la posición de salida
static t_coordinates find_exit_position(char **map, t_coordinates size) {
    t_coordinates pos;
    int row, col;

    pos.y = -1;
    pos.x = -1;
    row = 0;
    while (row < size.y) {
        col = 0;
        while (col < size.x) {
            if (map[row][col] == 'E') {
                pos.y = row;
                pos.x = col;
                return pos;
            }
            col++;
        }
        row++;
    }
    return pos; // Retorna una posición inválida si no se encuentra la salida
}

// Verificar si el mapa es accesible
int is_accessible(const char *filename) {
    char **map_copy;
    t_coordinates size;
    t_coordinates start;
    t_coordinates exit_position;
    game_t game;
    int i;

    // Leer el mapa desde el archivo
    map_copy = read_map_dup(filename, &size.x, &size.y);
    if (!map_copy) {
        ft_printf("Error al leer el mapa desde el archivo.\n");
        return 0;
    }

    // Inicializar la estructura del juego
    game.map = map_copy;
    game.map_width = size.x;
    game.map_height = size.y;
    game.player_x = 0; // Inicializar con valores adecuados
    game.player_y = 0; // Inicializar con valores adecuados
    game.total_collectables = 0; // Inicializar con valores adecuados
    game.collectables = NULL; // Inicializar con valores adecuados
    game.exit_position = (t_coordinates){0, 0}; // Inicializar con valores adecuados

    // Encontrar la posición inicial del jugador
    start = find_starting_position(map_copy, size);
    if (start.y == -1) {
        ft_printf("Posición inicial del jugador no encontrada.\n");
        free_map_dup(map_copy, size.y);
        return 0;
    }

    flood_fill(map_copy, size, start);

    // Encontrar la posición de salida
    exit_position = find_exit_position(map_copy, size);
    if (exit_position.y == -1 || exit_position.x == -1) {
        ft_printf("Posición de salida no encontrada.\n");
        free_map_dup(map_copy, size.y);
        return 0;
    }

    if (map_copy[exit_position.y][exit_position.x] != 'F') {
        ft_printf("Posición de salida no accesible. Coordenadas de salida: (%d, %d)\n",
                  exit_position.x, exit_position.y);
        free_map_dup(map_copy, size.y);
        return 0;
    }

    if (map_copy[game.player_y][game.player_x] != 'F') {
        ft_printf("Posición inicial del jugador no accesible.\n");
        free_map_dup(map_copy, size.y);
        return 0;
    }

    i = 0;
    while (i < game.total_collectables) {
        if (map_copy[game.collectables[i].y][game.collectables[i].x] != 'F') {
            ft_printf("Collectable en (%d, %d) no accesible.\n", game.collectables[i].x, game.collectables[i].y);
            free_map_dup(map_copy, size.y);
            return 0;
        }
        i++;
    }

    free_map_dup(map_copy, size.y);
    return 1;
}
