/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:49:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/12/14 09:46:58 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_texture(t_game *game, int x, int y, t_texture texture)
{
	mlx_put_image_to_window(game->mlx, game->win, texture.img,
		x * T_SIZE, y * T_SIZE);
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
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
