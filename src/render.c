/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:49:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/19 18:34:23 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_texture(game_t *game, int x, int y, texture_t texture)
{
	mlx_put_image_to_window(game->mlx, game->win, texture.img,
		x * TILE_SIZE, y * TILE_SIZE);
}

void	draw_map(game_t *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '1')
				draw_texture(game, x, y, game->wall_texture);
			else if (game->map[y][x] == 'P')
				draw_texture(game, x, y, game->player_texture);
			else if (game->map[y][x] == 'C')
				draw_texture(game, x, y, game->collectable_texture);
			else if (game->map[y][x] == 'E')
				draw_texture(game, x, y, game->exit_texture);
			else
				draw_texture(game, x, y, game->empty_texture);
			x++;
		}
		y++;
	}
}

void	draw_map_to_image(game_t *game, void *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, img, game->wall_texture.img,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, img, game->player_texture.img,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, img, game->collectable_texture.img,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, img, game->exit_texture.img,
					x * TILE_SIZE, y * TILE_SIZE);
			else
				mlx_put_image_to_window(game->mlx, img, game->empty_texture.img,
					x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	render_frame(game_t *game)
{
	void	*img;

	img = mlx_new_image(game->mlx, game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE);
	if (img == NULL)
		error_exit("Failed to create new image.");
	draw_map_to_image(game, img);
	mlx_put_image_to_window(game->mlx, game->win, img, 0, 0);
	mlx_destroy_image(game->mlx, img);
}
