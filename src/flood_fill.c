/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:49:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/22 16:53:00 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	fill_recursive(char **tab, t_coordinates size,
	t_coordinates pos, char target)
{
	t_coordinates	next_pos;

	if (pos.y < 0 || pos.y >= size.y || pos.x < 0 || pos.x >= size.x)
		return ;
	if (tab[pos.y][pos.x] == 'F' || tab[pos.y][pos.x] != target)
		return ;
	tab[pos.y][pos.x] = 'F';
	next_pos = (t_coordinates){pos.x, pos.y - 1};
	fill_recursive(tab, size, next_pos, target);
	next_pos = (t_coordinates){pos.x, pos.y + 1};
	fill_recursive(tab, size, next_pos, target);
	next_pos = (t_coordinates){pos.x - 1, pos.y};
	fill_recursive(tab, size, next_pos, target);
	next_pos = (t_coordinates){pos.x + 1, pos.y};
	fill_recursive(tab, size, next_pos, target);
}

static void	flood_fill(char **tab, t_coordinates size, t_coordinates begin)
{
	char	target;

	target = tab[begin.y][begin.x];
	fill_recursive(tab, size, begin, target);
}

static t_coordinates	find_starting_position(char **map, t_coordinates size)
{
	t_coordinates	pos;
	int				row;
	int				col;

	pos = (t_coordinates){-1, -1};
	row = 0;
	while (row < size.y)
	{
		col = 0;
		while (col < size.x)
		{
			if (map[row][col] == 'P')
			{
				pos.y = row;
				pos.x = col;
				return (pos);
			}
			col++;
		}
		row++;
	}
	return (pos);
}

static t_coordinates	find_exit_position(char **map, t_coordinates size)
{
	t_coordinates	pos;
	int				row;
	int				col;

	pos = (t_coordinates){-1, -1};
	row = 0;
	while (row < size.y)
	{
		col = 0;
		while (col < size.x)
		{
			if (map[row][col] == 'E')
			{
				pos.y = row;
				pos.x = col;
				return (pos);
			}
			col++;
		}
		row++;
	}
	return (pos);
}

int	is_accessible(const char *filename)
{
	char			**map;
	t_coordinates	size;
	t_coordinates	start;
	t_game			game;

	map = read_map(filename, &size.x, &size.y);
	validate_map(&game);
	start = find_starting_position(map, size);
	game.exit_position = find_exit_position(map, size);
	if (start.y == -1 || game.exit_position.y == -1
		|| map[start.y][start.x] != 'F'
		|| map[game.exit_position.y][game.exit_position.x] != 'F')
	{
		if (start.y == -1)
			ft_printf("Posición inicial del jugador no encontrada.\n");
		else
			ft_printf("Posición de salida no encontrada/accesible.\n");
		free_map(map, size.y);
		return (0);
	}
	flood_fill(map, size, start);
	free_map(map, size.y);
	return (1);
}
