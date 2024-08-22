/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspects.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:42:10 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/22 16:26:55 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	inspect_player_position(t_game *game, int x, int y)
{
	game->player_count++;
	game->player_x = x;
	game->player_y = y;
	if ((y > 0 && game->map[y - 1][x] == '1')
		&& (y < game->map_h - 1 && game->map[y + 1][x] == '1')
		&& (x > 0 && game->map[y][x - 1] == '1')
		&& (x < game->map_w - 1 && game->map[y][x + 1] == '1'))
		error_exit("The player is surrounded by walls.");
}

void	inspect_collectable_position(t_game *game, int x, int y)
{
	game->total_collectables++;
	if ((y > 0 && game->map[y - 1][x] == '1')
		&& (y < game->map_h - 1 && game->map[y + 1][x] == '1')
		&& (x > 0 && game->map[y][x - 1] == '1')
		&& (x < game->map_w - 1 && game->map[y][x + 1] == '1'))
		error_exit("A collectable is surrounded by walls.");
}

void	inspect_exit_position(t_game *game, int x, int y)
{
	game->exit_count++;
	if ((y > 0 && game->map[y - 1][x] == '1')
		&& (y < game->map_h - 1 && game->map[y + 1][x] == '1')
		&& (x > 0 && game->map[y][x - 1] == '1')
		&& (x < game->map_w - 1 && game->map[y][x + 1] == '1'))
		error_exit("The exit is surrounded by walls.");
}

void	update_map(char ***map, int *line_count, int *max_width, char *line)
{
	int	len;
	int	current_width;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	current_width = ft_strlen(line);
	if (current_width > *max_width)
		*max_width = current_width;
	*map = realloc(*map, (*line_count + 1) * sizeof(char *));
	if (!*map)
		error_exit("Memory allocation error.");
	(*map)[*line_count] = line;
	(*line_count)++;
}
