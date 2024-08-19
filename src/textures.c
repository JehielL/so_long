/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:49:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/19 18:36:40 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_texture(game_t *game, texture_t *texture, const char *file)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, (char *)file,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		ft_printf("Failed to load texture: %s\n", file);
		error_exit("Error loading texture.");
	}
}
