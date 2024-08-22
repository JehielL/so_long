/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:49:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/22 16:58:50 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	validate_map_dimensions(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_h)
	{
		if (ft_strlen(game->map[i]) != game->map_w)
			error_exit("Map is not rectangular.");
		if (game->map[i][0] != '1' || game->map[i][game->map_w - 1] != '1')
			error_exit("Map must be surrounded by walls.");
		i++;
	}
	i = 0;
	while (i < game->map_w)
	{
		if (game->map[0][i] != '1' || game->map[game->map_h - 1][i] != '1')
			error_exit("Map must be surrounded by walls.");
		i++;
	}
}

void	validate_map_contents(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = -1;
	game->player_count = 0;
	game->total_collectables = 0;
	game->exit_count = 0;
	game->collected = 0;
	while (++y < game->map_h)
	{
		x = -1;
		while (++x < game->map_w)
		{
			c = game->map[y][x];
			if (c == 'P')
				inspect_player_position(game, x, y);
			else if (c == 'E')
				inspect_exit_position(game, x, y);
			else if (c == 'C')
				inspect_collectable_position(game, x, y);
			else if (c != '0' && c != '1')
				error_exit("Unknown character in the map.");
		}
	}
}

void	validate_map(t_game *game)
{
	if (!game->map || game->map_h <= 0 || game->map_w <= 0)
		error_exit("Invalid map.");
	validate_map_dimensions(game);
	validate_map_contents(game);
	if (game->player_count != 1 || game->exit_count != 1
		|| game->total_collectables < 1)
	{
		error_exit("The map must have a player, an exit, "
			"and at least one collectible.");
	}
}

char	**read_map(const char *filename, int *width, int *height)
{
	int		fd;
	char	**map;
	int		line_count;
	int		max_width;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Could not open the map file.");
	map = NULL;
	line_count = 0;
	max_width = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		update_map(&map, &line_count, &max_width, line);
		line = get_next_line(fd);
	}
	close(fd);
	*height = line_count;
	*width = max_width;
	return (map);
}

void	free_map(char **map, int height)
{
	int	i;

	if (map)
	{
		i = 0;
		while (i < height)
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}
