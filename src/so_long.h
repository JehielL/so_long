// src/so_long.h
#ifndef SO_LONG_H
#define SO_LONG_H

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

void error_exit(const char *message);
void draw_texture(game_t *game, int x, int y, texture_t texture);
void draw_map(game_t *game);
void validate_map(game_t *game);
char **read_map(const char *filename, int *width, int *height);
void free_map(char **map, int height);
void load_texture(game_t *game, texture_t *texture, const char *file);
int key_press(int keycode, game_t *game);

#endif // SO_LONG_H

