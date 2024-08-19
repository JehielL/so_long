/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:49:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/19 18:37:22 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "../utils/ft_printf_42/ft_printf.h"
# include "../utils/gnl/get_next_line.h"
# include "../utils/libft/libft.h"

# define TILE_SIZE 40

typedef struct {
	void	*img;
	int		width;
	int		height;
}			texture_t;

typedef struct {
	int		x;
	int		y;
}			t_coordinates;

typedef struct {
	void			*mlx;
	void			*win;
	int				player_x;
	int				player_y;
	int				collected;
	int				moves;
	int				map_width;
	int				map_height;
	char			**map;
	texture_t		wall_texture;
	texture_t		player_texture;
	texture_t		collectable_texture;
	texture_t		exit_texture;
	texture_t		empty_texture;
	t_coordinates	exit_position;
	t_coordinates	*collectables;
	int				total_collectables;
}				game_t;

/* Función para imprimir mensajes de error y salir del programa. */
void	error_exit(const char *message);

/* Función para dibujar una textura en el mapa del juego. */
void	draw_texture(game_t *game, int x, int y, texture_t texture);

/* Función para dibujar el mapa en la ventana del juego. */
void	draw_map(game_t *game);

/* Función para validar el mapa del juego. */
void	validate_map(game_t *game);

/* Función para leer el mapa desde un archivo. */
char	**read_map(const char *filename, int *width, int *height);

/* Función para liberar la memoria del mapa. */
void	free_map(char **map, int height);

/* Función para cargar texturas desde archivos de imagen. */
void	load_texture(game_t *game, texture_t *texture, const char *file);

/* Función para procesar el movimiento del jugador en el mapa. */
void	process_movement(int new_x, int new_y, game_t *game);

/* Función para manejar las presiones de teclas. */
int		handle_key_press(int keycode, game_t *game);

/* Función para cerrar el juego de manera ordenada. */
int		close_game(game_t *game);

/* Funciones adicionales para validar dimensiones y contenidos del mapa */
void	validate_map_dimensions(game_t *game);
void	validate_map_contents(game_t *game);

/* Función para verificar la accesibilidad del mapa */
int		is_accessible(const char *filename);

/* Función para duplicar el mapa del juego */
char	**duplicate_map(game_t *game);

#endif /* SO_LONG_H */
