/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:49:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/19 18:35:03 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_game(game_t *game)
{
	ft_printf("Juego cerrado con exito\n");
	free_map(game->map, game->map_height);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

static int	validate(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (ft_strcmp(file + len - 5, "/.ber") == 0)
		return (0);
	if (ft_strcmp(file + len - 4, ".ber") == 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	game_t	game;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	game.mlx = mlx_init();
	if (validate(argv[1]) == 0)
		error_exit("map is invalid. its necessary .ber extension");
	if (!game.mlx)
		error_exit("Failed to initialize mlx.");
	game.map = read_map(argv[1], &game.map_width, &game.map_height);
	validate_map(&game);
	game.win = mlx_new_window(game.mlx, game.map_width * TILE_SIZE,
			game.map_height * TILE_SIZE, "So Long");
	if (!game.win)
		error_exit("Failed to create window.");
	load_texture(&game, &game.wall_texture, "textures/wallandfire.xpm");
	load_texture(&game, &game.player_texture, "textures/player_texture.xpm");
	load_texture(&game, &game.collectable_texture, "textures/collectables.xpm");
	load_texture(&game, &game.exit_texture, "textures/exit_texture.xpm");
	load_texture(&game, &game.empty_texture, "textures/cesped.xpm");
	draw_map(&game);
	mlx_key_hook(game.win, handle_key_press, &game);
	mlx_hook(game.win, 17, 0, (int (*)(void *))close_game, &game);
	mlx_loop(game.mlx);
	free_map(game.map, game.map_height);
	return (0);
}
