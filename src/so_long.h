/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:49:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/19 20:19:13 by jlinarez         ###   ########.fr       */
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

# define T_SIZE 40

typedef struct s_texture
{
	void	*img;
	int		width;
	int		height;
}	t_texture;

typedef struct s_coordinates
{
	int		x;
	int		y;
}	t_coordinates;

typedef struct t_game
{
	void			*mlx;
	void			*win;
	int				player_x;
	int				player_y;
	int				collected;
	int				moves;
	int				map_w;
	int				map_h;
	char			**map;
	t_texture		wall_texture;
	t_texture		player_texture;
	t_texture		collectable_texture;
	t_texture		exit_texture;
	t_texture		empty_texture;
	t_coordinates	exit_position;
	t_coordinates	*collectables;
	int				total_collectables;
}	t_game;

/* Función para imprimir mensajes de error y salir del programa. */
void	error_exit(const char *message);

/* Función para dibujar una textura en el mapa del juego. */
void	draw_texture(t_game *game, int x, int y, t_texture texture);

/* Función para dibujar el mapa en la ventana del juego. */
void	draw_map(t_game *game);

/* Función para validar el mapa del juego. */
void	validate_map(t_game *game);

/* Función para leer el mapa desde un archivo. */
char	**read_map(const char *filename, int *width, int *height);

/* Función para liberar la memoria del mapa. */
void	free_map(char **map, int height);

/* Función para cargar texturas desde archivos de imagen. */
void	load_texture(t_game *game, t_texture *texture, const char *file);

/* Función para procesar el movimiento del jugador en el mapa. */
void	process_movement(int new_x, int new_y, t_game *game);

/* Función para manejar las presiones de teclas. */
int		handle_key_press(int keycode, t_game *game);

/* Función para cerrar el juego de manera ordenada. */
int		close_game(t_game *game);

/* Funciones adicionales para validar dimensiones y contenidos del mapa. */
void	validate_map_dimensions(t_game *game);
void	validate_map_contents(t_game *game);

/* Función para verificar la accesibilidad del mapa. */
int		is_accessible(const char *filename);

/* Función para duplicar el mapa del juego. */
char	**duplicate_map(t_game *game);

#endif
