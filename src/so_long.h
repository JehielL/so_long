/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:49:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/22 16:27:24 by jlinarez         ###   ########.fr       */
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
	int				player_count;
	int				exit_count;
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

/* Function to print error messages and exit the program. */
void	error_exit(const char *message);

/* Function to draw a texture on the game map. */
void	draw_texture(t_game *game, int x, int y, t_texture texture);

/* Function to draw the map in the game window. */
void	draw_map(t_game *game);

/* Function to validate the game map. */
void	validate_map(t_game *game);

/* Function to read the map from a file. */
char	**read_map(const char *filename, int *width, int *height);

/* Function to free the memory of the map. */
void	free_map(char **map, int height);

/* Function to load textures from image files. */
void	load_texture(t_game *game, t_texture *texture, const char *file);

/* Function to process player movement on the map. */
void	process_movement(int new_x, int new_y, t_game *game);

/* Function to handle key presses. */
int		handle_key_press(int keycode, t_game *game);

/* Function to close the game properly. */
int		close_game(t_game *game);

/* Additional functions to validate map dimensions and contents. */
void	validate_map_dimensions(t_game *game);
void	validate_map_contents(t_game *game);

/* Function to check map accessibility. */
int		is_accessible(const char *filename);

/* Function to duplicate the game map. */
char	**duplicate_map(t_game *game);

/* Functions to inspect player, collectable, and exit positions. */
void	inspect_player_position(t_game *game, int x, int y);
void	inspect_collectable_position(t_game *game, int x, int y);
void	inspect_exit_position(t_game *game, int x, int y);
void	update_map(char ***map, int *line_count, int *max_width, char *line);

#endif
