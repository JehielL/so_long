/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:49:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/09/10 12:30:06 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(const char *message)
{
	ft_printf("Error\n%s\n", message);
	exit(EXIT_FAILURE);
}

int	handle_key_press(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x;
	new_y = game->player_y;
	if (keycode == 53 || keycode == 65307)
		close_game(game);
	else if (keycode == 119)
		new_y--;
	else if (keycode == 97)
		new_x--;
	else if (keycode == 115)
		new_y++;
	else if (keycode == 100)
		new_x++;
	if (new_x != game->player_x || new_y != game->player_y)
		process_movement(new_x, new_y, game);
	return (0);
}

static void	handle_special_cells(char cell, t_game *game)
{
	if (cell == 'E')
	{
		if (game->collected == game->total_collectables)
		{
			ft_printf("¡Has ganado!\n");
			close_game(game);
		}
		else
			ft_printf("Debes recoger todos los coleccionables"
				"antes de salir.\n");
	}
	else if (cell == 'C')
	{
		game->collected++;
		if (game->collected == game->total_collectables)
			ft_printf("¡Has coleccionado todos los ítems!\n");
	}
}

void	process_movement(int new_x, int new_y, t_game *game)
{
	char	cell;

	if (new_x < 0 || new_x >= game->map_w
		|| new_y < 0 || new_y >= game->map_h)
		return ;
	cell = game->map[new_y][new_x];
	if (cell == '1')
		return ;
	handle_special_cells(cell, game);
	if (cell == 'E' && game->collected != game->total_collectables)
		return ;
	game->map[game->player_y][game->player_x] = '0';
	game->player_x = new_x;
	game->player_y = new_y;
	game->map[new_y][new_x] = 'P';
	game->moves++;
	ft_printf("Movimientos realizados: %d\n", game->moves);
	mlx_clear_window(game->mlx, game->win);
	draw_map(game);
}
