#include "so_long.h"

// Función recursiva para realizar el flood fill
static void fill_recursive(char **tab, t_coordinates size, t_coordinates pos, char target) {
    t_coordinates next_pos;

    if (pos.y < 0 || pos.y >= size.y || pos.x < 0 || pos.x >= size.x)
        return;

    if (tab[pos.y][pos.x] == 'F' || tab[pos.y][pos.x] != target)
        return;

    // Marcar la posición como visitada
    tab[pos.y][pos.x] = 'F';

    // Recursión en las cuatro direcciones
    next_pos = (t_coordinates){pos.x, pos.y - 1}; // Arriba
    fill_recursive(tab, size, next_pos, target);

    next_pos = (t_coordinates){pos.x, pos.y + 1}; // Abajo
    fill_recursive(tab, size, next_pos, target);

    next_pos = (t_coordinates){pos.x - 1, pos.y}; // Izquierda
    fill_recursive(tab, size, next_pos, target);

    next_pos = (t_coordinates){pos.x + 1, pos.y}; // Derecha
    fill_recursive(tab, size, next_pos, target);
}

// Función para iniciar el flood fill
static void flood_fill(char **tab, t_coordinates size, t_coordinates begin) {
    char target = tab[begin.y][begin.x];
    fill_recursive(tab, size, begin, target);
}


// Función para encontrar la posición inicial del jugador
static t_coordinates find_starting_position(char **map, t_coordinates size) {
    t_coordinates pos = {-1, -1};
    int row = 0;
    
    while (row < size.y) {
        int col = 0;
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

// Función para encontrar la posición de salida
static t_coordinates find_exit_position(char **map, t_coordinates size) {
    t_coordinates pos = {-1, -1};
    int row = 0;
    
    while (row < size.y) {
        int col = 0;
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
    return pos;
}

// Función para verificar la accesibilidad del mapa
int is_accessible(const char *filename) {
    char **map;
    t_coordinates size;
    t_coordinates start;
    game_t game;

    // Leer y validar el mapa
    game.map = read_map(filename, &game.map_width, &game.map_height);
    validate_map(&game);

    // Leer el mapa desde el archivo
    map = read_map(filename, &size.x, &size.y);
    if (!map) {
        ft_printf("Error al leer el mapa desde el archivo.\n");
        return 0;
    }

    // Encontrar la posición inicial del jugador
    start = find_starting_position(map, size);
    if (start.y == -1) {
        ft_printf("Posición inicial del jugador no encontrada.\n");
        free_map(map, size.y);
        return 0;
    }

    flood_fill(map, size, start);

    // Imprimir el mapa después de flood_fill
    print_map(map, size.y);

    // Encontrar la posición de salida
    game.exit_position = find_exit_position(map, size);
    if (game.exit_position.y == -1 || game.exit_position.x == -1) {
        ft_printf("Posición de salida no encontrada.\n");
        free_map(map, size.y);
        return 0;
    }

    // Verificar si la posición de salida es accesible
    if (map[game.exit_position.y][game.exit_position.x] != 'F') {
        ft_printf("Posición de salida no accesible. Coordenadas de salida: (%d, %d)\n",
                  game.exit_position.x, game.exit_position.y);
        free_map(map, size.y);
        return 0;
    }

    // Verificar si la posición inicial del jugador es accesible
    if (map[start.y][start.x] != 'F') {
        ft_printf("Posición inicial del jugador no accesible.\n");
        free_map(map, size.y);
        return 0;
    }

    free_map(map, size.y);
    return 1;
}
