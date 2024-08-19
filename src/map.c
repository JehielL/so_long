/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:49:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/19 18:33:18 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	validate_map_dimensions(game_t *game)
{
	int	y;
	int	x;
	int	height;

	y = 0;
	while (y < game->map_height)
	{
		if (ft_strlen(game->map[y]) != game->map_width)
			error_exit("El mapa no es rectangular.");
		y++;
	}
	x = 0;
	while (x < game->map_width)
	{
		if (game->map[0][x] != '1' || game->map[game->map_height - 1][x] != '1')
			error_exit("El mapa debe estar rodeado de muros.");
		x++;
	}
	height = 0;
	while (height < game->map_height)
	{
		if (game->map[height][0] != '1'
			|| game->map[height][game->map_width - 1] != '1')
			error_exit("El mapa debe estar rodeado de muros.");
		height++;
	}
}

void	validate_map_contents(game_t *game)
{
	int	y;
	int	x;
	int	player_count;
	int	exit_count;

	y = 0;
	player_count = 0;
	exit_count = 0;
	game->total_collectables = 0;
	game->collected = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			char	c;

			c = game->map[y][x];
			if (c == 'P')
			{
				player_count++;
				game->player_x = x;
				game->player_y = y;
				if ((y > 0 && game->map[y - 1][x] == '1')
					&& (y < game->map_height - 1 && game->map[y + 1][x] == '1')
					&& (x > 0 && game->map[y][x - 1] == '1')
					&& (x < game->map_width - 1 && game->map[y][x + 1] == '1'))
					error_exit("El jugador está rodeado de paredes.");
			}
			else if (c == 'E')
			{
				exit_count++;
				if ((y > 0 && game->map[y - 1][x] == '1')
					&& (y < game->map_height - 1 && game->map[y + 1][x] == '1')
					&& (x > 0 && game->map[y][x - 1] == '1')
					&& (x < game->map_width - 1 && game->map[y][x + 1] == '1'))
					error_exit("La salida está rodeada de paredes.");
			}
			else if (c == 'C')
			{
				game->total_collectables++;
				if ((y > 0 && game->map[y - 1][x] == '1')
					&& (y < game->map_height - 1 && game->map[y + 1][x] == '1')
					&& (x > 0 && game->map[y][x - 1] == '1')
					&& (x < game->map_width - 1 && game->map[y][x + 1] == '1'))
					error_exit("Un coleccionable está rodeado de paredes.");
			}
			else if (c != '0' && c != '1')
			{
				ft_printf("Error: Carácter desconocido '0x%02x' en (%d, %d).\n",
					(unsigned char)c, y, x);
				error_exit("Carácter desconocido en el mapa.");
			}
			x++;
		}
		y++;
	}
	if (player_count != 1 || exit_count != 1 || game->total_collectables < 1)
		error_exit("El mapa debe tener un jugador, una salida y al menos un coleccionable.");
}

void	validate_map(game_t *game)
{
	if (!game->map || game->map_height <= 0 || game->map_width <= 0)
		error_exit("Mapa no válido.");
	validate_map_dimensions(game);
	validate_map_contents(game);
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
		error_exit("No se pudo abrir el archivo del mapa.");
	map = NULL;
	line_count = 0;
	max_width = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		int	len;

		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		int	current_width;

		current_width = ft_strlen(line);
		if (current_width > max_width)
			max_width = current_width;
		map = realloc(map, (line_count + 1) * sizeof(char *));
		if (!map)
			error_exit("Error de asignación de memoria.");
		map[line_count] = line;
		line_count++;
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
