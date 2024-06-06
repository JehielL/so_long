/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:27:36 by jlinarez          #+#    #+#             */
/*   Updated: 2024/06/06 14:27:41 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TILE_SIZE 20

typedef struct {
    void *mlx;
    void *win;
    int x;
    int y;
    int direction;
} snake_t;

void draw_square(snake_t *snake) {
    int i = snake->x;
    int j = snake->y;
    int x_end = i + TILE_SIZE;
    int y_end = j + TILE_SIZE;

    while (i < x_end) {
        j = snake->y;
        while (j < y_end) {
            mlx_pixel_put(snake->mlx, snake->win, i, j, 0x00FF00);
            j++;
        }
        i++;
    }
}

int key_press(int keycode, snake_t *snake) {
    if (keycode == 53) // Tecla 'ESC' en MacOS
        exit(0);
    else if (keycode == 65307) // Tecla 'ESC' en Linux
        exit(0);
    else if (keycode == 65361) // Tecla 'Izquierda'
        snake->direction = 0;
    else if (keycode == 65362) // Tecla 'Arriba'
        snake->direction = 1;
    else if (keycode == 65363) // Tecla 'Derecha'
        snake->direction = 2;
    else if (keycode == 65364) // Tecla 'Abajo'
        snake->direction = 3;
    return (0);
}

int update(snake_t *snake) {
    mlx_clear_window(snake->mlx, snake->win);
    if (snake->direction == 0) // Izquierda
        snake->x -= TILE_SIZE;
    else if (snake->direction == 1) // Arriba
        snake->y -= TILE_SIZE;
    else if (snake->direction == 2) // Derecha
        snake->x += TILE_SIZE;
    else if (snake->direction == 3) // Abajo
        snake->y += TILE_SIZE;

    // Lógica de límite de ventana
    if (snake->x < 0) snake->x = WINDOW_WIDTH - TILE_SIZE;
    if (snake->x >= WINDOW_WIDTH) snake->x = 0;
    if (snake->y < 0) snake->y = WINDOW_HEIGHT - TILE_SIZE;
    if (snake->y >= WINDOW_HEIGHT) snake->y = 0;

    draw_square(snake);
    return (0);
}

int main(void) {
    snake_t snake;
    snake.mlx = mlx_init();
    snake.win = mlx_new_window(snake.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Snake Game");
    snake.x = WINDOW_WIDTH / 2;
    snake.y = WINDOW_HEIGHT / 2;
    snake.direction = 2; // Empieza moviéndose hacia la derecha

    mlx_key_hook(snake.win, key_press, &snake);
    mlx_loop_hook(snake.mlx, update, &snake);
    mlx_loop(snake.mlx);

    return (0);
}

